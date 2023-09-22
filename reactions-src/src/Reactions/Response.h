//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "misc/Interface.h"
#include <iosfwd>

class Response : public Interface {
  public:
    virtual void print(std::ostream &output) = 0;
};
