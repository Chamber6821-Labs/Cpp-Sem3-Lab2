//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Scalar.h"
#include "owning/in.h"
#include <algorithm>
#include <cctype>
#include <string_view>

class FirstWord : public Scalar<std::string_view> {
    in<Scalar<std::string_view>> str;

  public:
    explicit FirstWord(in<Scalar<std::string_view>> str)
        : str(std::move(str)) {}

    auto value() -> std::string_view override {
        const auto value = str->value();
        return {value.begin(), std::ranges::find_if(value, isspace)};
    }
};
