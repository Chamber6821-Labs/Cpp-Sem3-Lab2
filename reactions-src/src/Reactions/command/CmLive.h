//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Reactions/Command.h"
#include "Reactions/misc/owning/in.h"
#include "Reactions/misc/owning/out.h"
#include <istream>
#include <string>

class CmLive : public Command {
    static auto lineOf(std::istream &input) -> std::string {
        std::string str;
        std::getline(input, str, '\n');
        return str;
    }

    std::string line;

  public:
    explicit CmLive(std::string line) : line(std::move(line)) {}

    explicit CmLive(std::istream &input) : CmLive(lineOf(input)) {}

    auto name() -> std::string_view override {
        return std::string_view{line}.substr(0, line.find(' '));
    }

    auto arguments() -> std::string_view override {
        const auto start = line.find(' ');
        if (start == std::string::npos) return "";
        return std::string_view{line}.substr(start);
    }
};
