//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Reaction.h"
#include "Reactions/misc/owning/makeOut.h"
#include "Reactions/response/RsEmpty.h"

class RcNothing : public Reaction {
  public:
    auto result(in<Command> /*unused*/) -> out<Response> override {
        return makeOut<RsEmpty>();
    }
};
