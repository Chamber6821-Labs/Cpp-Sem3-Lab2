//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Reactions/Front.h"
#include "Reactions/Reaction.h"
#include "Reactions/command/CmLive.h"
#include "Reactions/misc/owning/make.h"
#include <iostream>

class Console : public Front {
    in<Reaction> reaction{};
    std::string prompt;

  public:
    Console(in<Reaction> reaction, std::string prompt)
        : reaction(std::move(reaction)), prompt(std::move(prompt)) {}

    explicit Console(in<Reaction> reaction)
        : Console(std::move(reaction), "") {}

    void start(in<Exit> exit) override {
        while (not exit->ready()) {
            std::cout << prompt;
            reaction->result(make<CmLive>(std::cin))->print(std::cout);
        }
    }
};
