//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Reaction.h"
#include "Reactions/response/RsGlued.h"
#include <iterator>
#include <ranges>
#include <vector>

class RcGlued : public Reaction {
    std::vector<in<Reaction>> parts{};

  public:
    template <std::input_iterator Iterator>
    RcGlued(Iterator begin, Iterator end) : parts(begin, end) {}

    RcGlued(std::initializer_list<in<Reaction>> parts)
        : RcGlued(parts.begin(), parts.end()) {}

    template <std::convertible_to<in<Reaction>>... Types>
    explicit RcGlued(Types... parts) : RcGlued({parts...}) {}

    auto result(in<Command> command) -> out<Response> override {
        auto responses = parts | std::views::transform([&](auto x) {
                             return x->result(command);
                         });
        return makeOut<RsGlued>(responses.begin(), responses.end());
    }
};
