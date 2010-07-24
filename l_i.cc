#pragma once

#include <map>
#include "l_c.h"
using std::map;

value& context::operator [] (const symbol& s) {
    if (dict.count(s)) {
        return dict[s];
    } else if (parent && parent->contains(s)) {
        return (*parent)[s];
    } else {
        return dict[s];
    }
}

bool context::contains(const symbol& s) {
    return dict.count(s) || (parent && parent->contains(s));
}

