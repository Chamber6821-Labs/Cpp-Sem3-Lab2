
//
// Created by Ivan on 25.05.2023.
//

#include "Reactions/misc/StringOf.h"
#include "../doctest-nolint.h"
#include "Reactions/misc/owning/make.h"

TEST_SUITE("StringOf") {
    TEST_CASE("should copy string") {
        auto temporaryObject = make<std::string>("Long string");
        auto string = StringOf(*temporaryObject);
        temporaryObject.reset(); // Call destructor of the temporary object
        REQUIRE_EQ(std::string(string.value()), std::string("Long string"));
    }
}
