//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Fork.h"
#include "Reactions/Reaction.h"
#include <regex>

class FkArgRegex : public Fork {
    std::regex regex;
    in<Reaction> reaction{};

  public:
    FkArgRegex(std::regex regex, in<Reaction> reaction)
        : regex(std::move(regex)), reaction(std::move(reaction)) {}

    FkArgRegex(std::string_view regex, in<Reaction> reaction)
        : FkArgRegex(std::regex(regex.begin(), regex.end(),
                                std::regex_constants::ECMAScript),
                     std::move(reaction)) {}

    auto route(in<Command> command) -> std::optional<out<Response>> override;
};
