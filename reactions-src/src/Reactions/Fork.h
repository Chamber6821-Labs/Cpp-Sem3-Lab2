//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Command.h"
#include "Response.h"
#include "misc/Interface.h"
#include "misc/owning/in.h"
#include "misc/owning/out.h"
#include <optional>

class Fork : public Interface {
  public:
    virtual auto route(in<Command>) -> std::optional<out<Response>> = 0;
};
