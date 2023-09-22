//
// Created by Ivan on 30.05.2023.
//

#include "Reactions/command/NthArg.h"
#include "../doctest-nolint.h"
#include "Reactions/command/CmLive.h"
#include "Reactions/misc/owning/make.h"
#include <string>

TEST_SUITE("NthArg") {
    TEST_CASE("should be equal") {
        const auto command = std::string("com arg");
        const auto arg = make<NthArg>(make<CmLive>(command), 0)->value();
        CHECK_EQ(arg, "arg");
    }
}
