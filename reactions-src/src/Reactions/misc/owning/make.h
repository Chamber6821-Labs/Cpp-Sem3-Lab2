//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include <memory>

template <class T, class... Args>
auto make(Args &&...args) {
    return std::make_shared<T>(args...);
}

template <template <class...> class T, class... Args>
auto make(Args &&...args) {
    return std::make_shared<T<Args...>>(args...);
}
