//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Front.h"
#include <string_view>

class Welcome : public Front {
    std::string_view welcome;
    in<Front> front;

  public:
    Welcome(std::string_view welcome, in<Front> front)
        : welcome(welcome), front(std::move(front)) {}

    void start(in<Exit> exit) override {
        std::cout << welcome;
        front->start(exit);
    }
};
