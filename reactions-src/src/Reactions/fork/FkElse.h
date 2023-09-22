//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Reactions/Fork.h"
#include "Reactions/Reaction.h"

class FkElse : public Fork {
    in<Reaction> reaction{};

  public:
    explicit FkElse(in<Reaction> reaction) : reaction(std::move(reaction)) {}

    auto route(in<Command> request) -> std::optional<out<Response>> override {
        return {reaction->result(std::move(request))};
    }
};
