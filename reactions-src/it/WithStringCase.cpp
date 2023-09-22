//
// Created by Ivan051N1N on 10.05.2023.
//

#include "Reactions/misc/owning/make.h"
#include "Reactions/response/RsText.h"
#include "doctest-nolint.h"
#include <sstream>

TEST_SUITE("Internal UB") {
    TEST_CASE("make RsText from temporary string") {
        auto temporaryObject = make<std::string>("Long string");
        auto text = make<RsText>(*temporaryObject);
        temporaryObject.reset(); // Call destructor of the temporary object

        std::stringstream buffer;
        text->print(buffer);

        REQUIRE(buffer.view() == "Long string");
    }
}
