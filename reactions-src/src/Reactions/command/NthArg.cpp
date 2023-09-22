//
// Created by Ivan on 10.05.2023.
//

#include "NthArg.h"
#include "Reactions/misc/FirstWord.h"
#include "Reactions/misc/LeftTrimmed.h"
#include "Reactions/misc/StringOf.h"
#include "Reactions/misc/owning/make.h"
#include <stdexcept>
#include <string>

NthArg::NthArg(in<Command> command, int number)
    : command(std::move(command)), number(number) {}

auto NthArg::value() -> std::string {
    try {
        if (number < 0)
            throw std::invalid_argument(
                "Argument number less than zero (number = '" +
                std::to_string(number) + "')");
        const auto arguments = command->arguments();
        auto word = FirstWord(make<LeftTrimmed>(make<StringOf>(arguments)));
        for (int i = 0; i < number; i++) {
            word = FirstWord(make<LeftTrimmed>(
                make<StringOf>(word.value().end(), arguments.end())));
        }
        return std::string(word.value());
    } catch (...) {
        std::throw_with_nested(std::invalid_argument(
            "Failed to get " + std::to_string(number) + "th argument"));
    }
}
