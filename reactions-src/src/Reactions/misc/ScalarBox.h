//
// Created by Ivan on 06.08.2023.
//

#pragma once

#include "Scalar.h"

template <class T>
class ScalarBox : public Scalar<T> {
    T _value;

  public:
    ScalarBox(T value) : _value(value) {}

    virtual auto value() -> T { return _value; }
};
