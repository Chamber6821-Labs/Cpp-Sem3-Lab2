//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Scalar.h"
#include "owning/in.h"
#include <algorithm>
#include <cctype>
#include <string_view>

class LeftTrimmed : public Scalar<std::string_view> {
    in<Scalar<std::string_view>> str;

  public:
    explicit LeftTrimmed(in<Scalar<std::string_view>> str)
        : str(std::move(str)) {}

    auto value() -> std::string_view override {
        return {std::ranges::find_if_not(
                    str->value(), [](auto x) { return std::isspace(x); }),
                str->value().end()};
    }
};
