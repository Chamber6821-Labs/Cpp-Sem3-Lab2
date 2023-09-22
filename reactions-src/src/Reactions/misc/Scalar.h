//
// Created by Ivan on 05.05.2023.
//

#pragma once

#include "Interface.h"

template <class T>
class Scalar : public Interface {
  public:
    virtual auto value() -> T = 0;
};
