#include "Reactions/exit/ExFlag.h"
#include "Reactions/fork/FkArgRegex.h"
#include "Reactions/fork/FkElse.h"
#include "Reactions/fork/FkWithName.h"
#include "Reactions/front/Console.h"
#include "Reactions/parameter/PrPositiveInt.h"
#include "Reactions/reaction/RcExit.h"
#include "Reactions/reaction/RcFork.h"
#include "Reactions/reaction/RcMapped.h"
#include "Reactions/reaction/RcNothing.h"
#include "Reactions/reaction/RcNothrow.h"
#include "Reactions/reaction/RcParameterized.h"
#include "Reactions/reaction/RcText.h"
#include "Reactions/reaction/RcWithEffect.h"
#include "Reactions/response/RsGlued.h"
#include "task.h"
#include <algorithm>
#include <chrono>
#include <format>
#include <ranges>

std::vector<BadTask> &operator+=(std::vector<BadTask> &left, BadTask right) {
  left.push_back(std::move(right));
  return left;
}

std::vector<BadTask> operator+(std::vector<BadTask> left, BadTask right) {
  left += std::move(right);
  return std::move(left);
}

std::vector<BadTask> &
operator-=(std::vector<BadTask> &left, const BadTask &right) {
  auto target = std::find(left.begin(), left.end(), right);
  if (target != left.end()) left.erase(target);
  return left;
}

std::vector<BadTask>
operator-(std::vector<BadTask> left, const BadTask &right) {
  left -= right;
  return std::move(left);
}

int main() {
  auto flag = make<ExFlag>();
  auto tasks = std::vector<BadTask>();

  make<Console>(
    make<RcNothrow>(make<RcFork>(
      make<FkWithName>("", make<RcNothing>()),
      make<FkWithName>("exit", make<RcExit>(flag)),
      make<FkWithName>("list", make<RcMapped>([&](auto) {
                         auto range =
                           std::views::iota(size_t(0), tasks.size()) |
                           std::views::transform([&](int index) {
                             return make<RsGlued>(
                               make<RsText>(std::to_string(index)),
                               make<RsText>(". "),
                               make<RsText>(std::format(
                                 "[{:%F %T}] ",
                                 tasks[index].creationTime()
                               )),
                               make<RsText>(tasks[index].prompt()),
                               make<RsText>("\n")
                             );
                           });
                         return makeOut<RsGlued>(range.begin(), range.end());
                       })),
      make<FkWithName>("add", make<RcWithEffect>([&](const in<Command> &c) {
                         tasks.emplace_back(
                           std::chrono::time_point_cast<std::chrono::seconds>(
                             std::chrono::system_clock::now()
                           ),
                           std::string(c->arguments())
                         );
                       })),
      make<FkWithName>(
        "remove",
        make<RcFork>(
          make<FkArgRegex>(
            R"(\d+)",
            make<RcParameterized<unsigned int>>(
              make<PrPositiveInt>(),
              [&](unsigned int index) {
                if (index >= tasks.size())
                  throw std::runtime_error("Index too big");
                tasks.erase(tasks.begin() + index);
                return makeOut<RsEmpty>();
              }
            )
          ),
          make<FkElse>(make<RcText>("Invalid argument. Expected: remove <index>"
          ))
        )
      )
    )),
    ">"
  )
    ->start(flag);
  return 0;
}
