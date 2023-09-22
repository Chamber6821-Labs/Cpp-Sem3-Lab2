//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Response.h"
#include <functional>

class RsMapped : public Response {
    std::function<void(std::ostream &output)> map;

  public:
    explicit RsMapped(decltype(map) map) : map(std::move(map)) {}

    void print(std::ostream &output) override { map(output); }
};
