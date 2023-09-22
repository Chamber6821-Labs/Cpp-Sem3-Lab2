//
// Created by Ivan on 06.05.2023.
//

#pragma once

#include "RcNothing.h"
#include "Reactions/Reaction.h"
#include "Reactions/misc/owning/in.h"
#include "Reactions/misc/owning/make.h"
#include "Reactions/misc/owning/out.h"
#include <functional>

class RcWithEffect : public Reaction {
    in<Reaction> reaction{};
    std::function<void(in<Command>)> effect;

  public:
    RcWithEffect(in<Reaction> reaction, std::function<void(in<Command>)> effect)
        : reaction(std::move(reaction)), effect(std::move(effect)) {}

    RcWithEffect(in<Reaction> reaction, const std::function<void()> &effect)
        : RcWithEffect(std::move(reaction), [effect](auto) { effect(); }) {}

    explicit RcWithEffect(std::function<void(in<Command>)> effect)
        : RcWithEffect(make<RcNothing>(), std::move(effect)) {}

    explicit RcWithEffect(const std::function<void()> &effect)
        : RcWithEffect(make<RcNothing>(), effect) {}

    auto result(in<Command> command) -> out<Response> override;
};
