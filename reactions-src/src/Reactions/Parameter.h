//
// Created by Ivan on 07.05.2023.
//

#pragma once

#include "command/Argument.h"
#include "misc/Interface.h"
#include "misc/owning/in.h"

template <class T>
class Parameter : public Interface {
  public:
    virtual auto valueOf(in<Argument> argument) -> T = 0;
};
