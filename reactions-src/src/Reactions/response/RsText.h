//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Reactions/Response.h"
#include "Reactions/misc/Scalar.h"
#include "Reactions/misc/StringOf.h"
#include "Reactions/misc/owning/in.h"
#include "Reactions/misc/owning/make.h"
#include <iostream>
#include <string_view>

class RsText : public Response {
    in<Scalar<std::string_view>> str{};

  public:
    explicit RsText(in<Scalar<std::string_view>> str) : str(std::move(str)) {}

    explicit RsText(std::string_view str) : RsText(make<StringOf>(str)) {}

    void print(std::ostream &output) override { output << str->value(); };
};
