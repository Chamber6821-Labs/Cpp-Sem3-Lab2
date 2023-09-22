//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Reactions/Exit.h"

class ExFlag : public Exit {
    bool state;

  public:
    explicit ExFlag(bool state) : state(state) {}

    explicit ExFlag() : state(false) {}

    void up() { state = true; }

    auto ready() -> bool override { return state; }
};
