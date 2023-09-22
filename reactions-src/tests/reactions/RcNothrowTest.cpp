//
// Created by Ivan on 30.05.2023.
//

#include "Reactions/reaction/RcNothrow.h"
#include "../doctest-nolint.h"
#include "Reactions/command/CmEmpty.h"
#include "Reactions/misc/owning/make.h"
#include "Reactions/response/RsMapped.h"
#include <sstream>
#include <string>

class ShooterReaction : public Reaction {
    std::string message;

  public:
    explicit ShooterReaction(std::string message)
        : message(std::move(message)) {}

    auto result(in<Command> /*unused*/) -> out<Response> override {
        return makeOut<RsMapped>([this](auto &) {
            throw std::runtime_error(message);
        });
    }
};

TEST_SUITE("RcNothrow") {
    TEST_CASE("should not throw exception") {
        std::stringstream output;
        CHECK_NOTHROW(make<RcNothrow>(make<ShooterReaction>("Bang!"))
                          ->result(make<CmEmpty>())
                          ->print(output););
        CHECK(output.view().data() == doctest::Contains("Bang!"));
    }
}
