//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Command.h"
#include "Response.h"
#include "misc/Interface.h"
#include "misc/owning/in.h"
#include "misc/owning/out.h"

class Reaction : public Interface {
  public:
    virtual auto result(in<Command>) -> out<Response> = 0;
};
