//
// Created by Ivan on 30.05.2023.
//

#include "Reactions/command/CmEmpty.h"
#include "Reactions/reaction/RcNothrow.h"
#include "Reactions/reaction/RcWithEffect.h"
#include "doctest-nolint.h"
#include <iostream>
#include <stdexcept>

TEST_SUITE("RcNothrow") {
    TEST_CASE("should not throw exception") {
        CHECK_NOTHROW(make<RcNothrow>(make<RcWithEffect>([]() {
                          // this exception will be thrown in RsMapped::print
                          // and will not be caught by RcNothrow
                          throw std::exception();
                      }))
                          ->result(make<CmEmpty>())
                          ->print(std::cout););
    }
}
