//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Front.h"
#include <string_view>

class Farewell : public Front {
    std::string_view farewell;
    in<Front> front;

  public:
    Farewell(in<Front> front, std::string_view farewell)
        : front(std::move(front)), farewell(farewell) {}

    void start(in<Exit> exit) override {
        front->start(exit);
        std::cout << farewell;
    }
};
