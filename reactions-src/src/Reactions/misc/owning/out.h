//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include <memory>

template <class T>
using out = std::unique_ptr<T>;
