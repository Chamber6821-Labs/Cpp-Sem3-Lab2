//
// Created by Ivan on 10.05.2023.
//

#pragma once

#include "Reactions/Response.h"
#include "Reactions/misc/owning/in.h"
#include <iterator>
#include <vector>

class RsGlued : public Response {
    std::vector<in<Response>> parts{};

  public:
    template <std::input_iterator Iterator>
    RsGlued(Iterator begin, Iterator end) : parts(begin, end) {}

    RsGlued(std::initializer_list<in<Response>> parts)
        : RsGlued(parts.begin(), parts.end()) {}

    template <std::convertible_to<in<Response>>... Types>
    explicit RsGlued(Types... parts) : RsGlued({parts...}) {}

    void print(std::ostream &output) override {
        for (auto &part : parts) {
            part->print(output);
        }
    }
};
