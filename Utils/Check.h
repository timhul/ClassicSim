#pragma once

#include <stdexcept>

#define check(p, msg) \
    if (p == false) \
    throw std::logic_error(msg)
