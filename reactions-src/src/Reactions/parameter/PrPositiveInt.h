//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Command.h"
#include "Reactions/Parameter.h"
#include "Reactions/misc/owning/in.h"
#include "Reactions/misc/owning/make.h"
#include <charconv>
#include <stdexcept>

class PrPositiveInt : public Parameter<unsigned int> {
  public:
    auto valueOf(in<Argument> argument) -> unsigned int override {
        try {
            const auto arg = argument->value();
            unsigned int x = 0;
            const auto [ptr, error] =
                std::from_chars(arg.data(), arg.data() + arg.size(), x);
            if (error == std::errc::invalid_argument or
                error == std::errc::result_out_of_range)
                throw std::invalid_argument("Argument '" + std::string(arg) +
                                            "' is not unsigned int");
            return x;
        } catch (...) {
            std::throw_with_nested(
                std::invalid_argument("Failed to parse int from argument"));
        }
    }
};
