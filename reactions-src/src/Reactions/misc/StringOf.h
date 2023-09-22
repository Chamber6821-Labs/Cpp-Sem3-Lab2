//
// Created by Ivan on 10.05.2023.
//

#pragma once

#include "Scalar.h"
#include <string>
#include <utility>

class StringOf : public Scalar<std::string_view> {
    std::string string;

  public:
    explicit StringOf(std::string string) : string(std::move(string)) {}

    explicit StringOf(std::string_view view) : string(view) {}

    StringOf(std::string::const_iterator begin, std::string::const_iterator end)
        : StringOf(std::string{begin, end}) {}

    StringOf(
        std::string_view::const_iterator begin,
        std::string_view::const_iterator end
    )
        : StringOf(std::string_view{begin, end}) {}

    auto value() -> std::string_view override { return string; }
};
