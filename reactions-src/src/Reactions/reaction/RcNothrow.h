//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Reaction.h"
#include "Reactions/misc/owning/makeOut.h"
#include "Reactions/response/RsError.h"
#include "Reactions/response/RsMapped.h"

class RcNothrow : public Reaction {
    in<Reaction> wrapped{};

  public:
    explicit RcNothrow(in<Reaction> wrapped) : wrapped(std::move(wrapped)) {}

    auto result(in<Command> command) -> out<Response> override {
        return makeOut<RsMapped>([=, *this](auto &output) {
            try {
                wrapped->result(command)->print(output);
            } catch (const std::exception &e) {
                return RsError(e).print(output);
            }
        });
    }
};
