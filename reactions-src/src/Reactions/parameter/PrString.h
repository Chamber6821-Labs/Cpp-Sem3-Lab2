//
// Created by Ivan on 07.05.2023.
//

#pragma once

#include "Reactions/Parameter.h"

class PrString : public Parameter<std::string> {
  public:
    PrString() = default;

    auto valueOf(in<Argument> argument) -> std::string override {
        return argument->value();
    }
};
