//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "misc/Interface.h"
#include <string_view>

class Command : public Interface {
  public:
    virtual auto name() -> std::string_view = 0;
    virtual auto arguments() -> std::string_view = 0;
};
