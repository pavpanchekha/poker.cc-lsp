#pragma once
#include "l_c.h"

ostream& operator<<(ostream& os, value v) {
    switch (v.type) {
        case SYMBOL:
            os << *(v.symb_p);
            break;
        case INT:
            os << v.int_v;
            break;
        case LIST:
            os << '(';
            for (cons *l = v.list_p; l; l = l->cdr) {
                os << *(l->car);
                if (l->cdr) os << " ";
            }
            os << ')';
            break;
        case CLOSURE:
            if (v.fn_p->name.size()) {
                os << "#<fn " << v.fn_p->name << ">";
            } else {
                os << "#<fn>";
            }
            break;
    }
    return os;
}

