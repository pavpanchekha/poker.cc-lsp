#pragma once

#include "l_p.cc"
#include "l_l.cc"

using namespace std;

value eval(value *sexp, context *ctx) throw (lisp_error) {
    switch (sexp->type) {
        case INT: case CLOSURE:
            return *sexp;
            break;
        case SYMBOL:
            if (!sexp->symb_p->size()) return value(); // to work around bug in parser
            // Commented out because of bugs elsewhere. Let's ignore them and hope they go away.
            return (*ctx)[*(sexp->symb_p)];
            break;
    }

    cons *s = sexp->list_p;
    if (!s->car) return value(); // No idea why this is necessary
    
    value callee;
    try {
        callee = eval(s->car, ctx);
    } catch (lisp_error e) {
        if (!e.was_printed) {
            cerr << "Error: " << e.what() << endl;
            e.was_printed = true;
        }
        cerr << "\t evaluating `" << *(s->car) << "`" << endl;
        throw e;
    }

    try {
        CHECK(callee.type == CLOSURE, "Attempted to call a non-function");
        // As of now, sexp is a bunch of values
        value ret = (*callee.fn_p)(eval, ctx, sexp->list_p->cdr);
        //cerr << "->" << ret << endl;
        return ret;
    } catch (lisp_error e) {
        if (!e.was_printed) {
            cerr << "Error: " << e.what() << endl;
            e.was_printed = true;
        }
        cerr << "\t in         (" << callee << " ...)" << endl;
        throw e;
    }
}

value eval_all(cons *k, context *ctx) {
    value v;
    for (; k; k = k->cdr) {
        v = eval(k->car, ctx);
    }
    return v;
}
