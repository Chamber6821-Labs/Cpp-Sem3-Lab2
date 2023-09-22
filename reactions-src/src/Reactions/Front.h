//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Exit.h"
#include "misc/Interface.h"
#include "misc/owning/in.h"

class Front : public Interface {
  public:
    virtual void start(in<Exit>) = 0;
};
