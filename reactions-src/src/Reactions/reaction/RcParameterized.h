//
// Created by Ivan on 07.05.2023.
//

#pragma once

#include "Reactions/Parameter.h"
#include "Reactions/Reaction.h"
#include "Reactions/command/NthArg.h"
#include "Reactions/misc/owning/make.h"
#include "Reactions/response/RsEmpty.h"
#include <concepts>
#include <functional>
#include <tuple>
#include <utility>

template <class... Args>
class RcParameterized : public Reaction {
    std::tuple<in<Parameter<Args>>...> parameters;
    std::function<out<Response>(Args...)> func;

    template <class... Params, std::size_t... Is>
    inline auto wrap(in<Command> &command,
                     std::index_sequence<Is...> /*unused*/, Params... params) {
        return func(params->valueOf(make<NthArg>(command, Is))...);
    }

  public:
    explicit RcParameterized(
        in<Parameter<Args>>... parameters, decltype(func) func
    )
        : parameters(parameters...), func(std::move(func)) {}

    auto result(in<Command> command) -> out<Response> override {
        return std::apply(
            [&, this](auto... x) {
                return wrap(command,
                            std::make_index_sequence<sizeof...(Args)>(), x...);
            },
            parameters);
    }
};
