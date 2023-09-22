//
// Created by Ivan on 10.05.2023.
//

#include "Reactions/exit/ExNever.h"
#include "Reactions/fork/FkElse.h"
#include "Reactions/fork/FkWithName.h"
#include "Reactions/front/Console.h"
#include "Reactions/reaction/RcFork.h"
#include "Reactions/reaction/RcText.h"

// NOLINTNEXTLINE(bugprone-exception-escape)
auto main() -> int {
    make<Console>(
        make<RcFork>(
            make<FkWithName>("welcome", make<RcText>("Hello, World!\n")),
            make<FkElse>(make<RcText>("Unknown command!\n"))
        ),
        ">"
    )
        ->start(make<ExNever>());
}
