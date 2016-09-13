//
//  Swap.cpp
//  Kolkakoli
//
//  Created by Liam Magee on 30/08/2016.
//
//

#include "Swap.hpp"

namespace std {
    template <> struct hash<Swap> {
        std::size_t operator()(const Swap& o) const {
            int ca = o.cookieA->row * 1000000 + o.cookieA->col;
            int cb = o.cookieB->row * 1000000 + o.cookieB->col;
            std::size_t h = ca ^ cb;
            return h;
        }
    };
}

bool Swap::operator==(const Swap &other) const {
    if (cookieA->col == other.cookieA->col && cookieA->row == other.cookieA->row &&
        cookieB->col == other.cookieB->col && cookieB->row == other.cookieB->row)
        return true;
    if (cookieA->col == other.cookieB->col && cookieA->row == other.cookieB->row &&
        cookieB->col == other.cookieA->col && cookieB->row == other.cookieA->row)
        return true;
    return false;
}