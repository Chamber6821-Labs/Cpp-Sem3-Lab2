//
// Created by Ivan on 09.05.2023.
//

#include "RcFork.h"
#include "Reactions/misc/CommandAsString.h"
#include <stdexcept>

auto RcFork::result(in<Command> command) -> out<Response> {
    try {
        for (const auto &fork : forks) {
            auto opt = fork->route(command);
            if (opt.has_value()) return std::move(opt.value());
        }
        throw std::domain_error("Command '" + CommandAsString(command).value() +
                                "' not matched");
    } catch (...) {
        // NOLINTNEXTLINE(bugprone-throw-keyword-missing)
        std::throw_with_nested(std::runtime_error("Failed to select fork"));
    }
}
