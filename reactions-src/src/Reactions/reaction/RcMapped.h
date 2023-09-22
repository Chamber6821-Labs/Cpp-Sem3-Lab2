//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Reaction.h"
#include "Reactions/response/RsEmpty.h"
#include <functional>

class RcMapped : public Reaction {
  public:
    using Func = std::function<out<Response>(in<Command> &)>;

  private:
    Func mapped{};

  public:
    explicit RcMapped(Func mapped) : mapped(std::move(mapped)) {}

    explicit RcMapped(const std::function<out<Response>()> &mapped)
        : RcMapped(Func([mapped](auto) { return mapped(); })) {}

    auto result(in<Command> command) -> out<Response> override {
        return mapped(command);
    }
};
