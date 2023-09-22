//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Reactions/Exit.h"

class ExNever : public Exit {
  public:
    auto ready() -> bool override { return false; }
};
