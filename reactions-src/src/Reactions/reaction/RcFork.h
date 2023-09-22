//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Reactions/Fork.h"
#include "Reactions/Reaction.h"
#include <vector>

class RcFork : public Reaction {
    std::vector<in<Fork>> forks{};

  public:
    template <std::input_iterator Iterator>
    RcFork(Iterator begin, Iterator end) : forks(begin, end) {}

    RcFork(std::initializer_list<in<Fork>> forks)
        : RcFork(forks.begin(), forks.end()) {}

    template <std::convertible_to<in<Fork>>... Types>
    explicit RcFork(Types... forks) : RcFork({forks...}) {}

    auto result(in<Command> command) -> out<Response> override;
};
