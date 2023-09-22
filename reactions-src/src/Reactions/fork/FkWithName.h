//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Reactions/Fork.h"
#include "Reactions/Reaction.h"
#include "Reactions/misc/owning/make.h"
#include <stdexcept>

class FkWithName : public Fork {
    std::string_view name;
    in<Reaction> reaction{};

  public:
    FkWithName(std::string_view name, in<Reaction> reaction)
        : name(name), reaction(std::move(reaction)) {}

    auto route(in<Command> command) -> std::optional<out<Response>> override {
        try {
            if (command->name() != name) return std::nullopt;
            return {reaction->result(std::move(command))};
        } catch (...) {
            std::throw_with_nested(
                std::runtime_error("Failed to react to command")
            );
        }
    }
};
