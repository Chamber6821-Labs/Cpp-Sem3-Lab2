//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "misc/Interface.h"

class Exit : public Interface {
  public:
    virtual auto ready() -> bool = 0;
};
