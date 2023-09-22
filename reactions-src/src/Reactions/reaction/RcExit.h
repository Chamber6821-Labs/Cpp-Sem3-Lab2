//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Reaction.h"
#include "Reactions/exit/ExFlag.h"
#include "Reactions/misc/owning/makeOut.h"
#include "Reactions/response/RsEmpty.h"

class RcExit : public Reaction {
    in<ExFlag> exit{};

  public:
    explicit RcExit(in<ExFlag> exit) : exit(std::move(exit)) {}

    auto result(in<Command> /*unused*/) -> out<Response> override {
        exit->up();
        return makeOut<RsEmpty>();
    }
};
