//
// Created by Ivan on 10.05.2023.
//

#include "FkArgRegex.h"
#include <stdexcept>

auto FkArgRegex::route(in<Command> command) -> std::optional<out<Response>> {
    try {
        const auto args = command->arguments();
        if (not std::regex_search(args.begin(), args.end(), regex))
            return std::nullopt;
        return reaction->result(std::move(command));
    } catch (...) {
        std::throw_with_nested(
            std::runtime_error("Failed to match by regular expression"));
    }
}
