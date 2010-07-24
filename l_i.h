#pragma once

#include <map>
#include "l_c.h"
using std::map;

class context {
    private:
        map<symbol, value> dict;
        context *parent;

    public:
        context(map<symbol, value>& d, context *p = 0): dict(d), parent(p) {}
        value& operator [] (const symbol& s);
        bool contains(const symbol& s);
};
