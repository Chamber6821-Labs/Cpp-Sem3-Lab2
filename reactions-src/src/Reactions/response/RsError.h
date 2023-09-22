//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reactions/Response.h"
#include <ostream>
#include <stdexcept>
#include <string>

class RsError : public Response {
    std::string error{};

    // NOLINTNEXTLINE(misc-no-recursion)
    static auto stringify(const std::exception &e, int level) -> std::string {
        auto part = std::string(level, ' ') + "exception: " + e.what() + '\n';
        try {
            std::rethrow_if_nested(e);
            return part;
        } catch (const std::exception &nestedException) {
            return part + stringify(nestedException, level + 1);
        }
    }

  public:
    explicit RsError(const std::exception &error)
        : error(stringify(error, 0)) {}

    void print(std::ostream &output) override { output << error; }
};
