#pragma once

#include <string>
#include <iostream>
using std::cerr;
using std::endl;
using std::string;
using std::ostream;

#include <exception>
struct lisp_error : public std::exception {
    string message;
    bool was_printed;
    
    lisp_error(string _message): message(_message) {}
    ~lisp_error() throw () {}

    virtual const char *what() const throw() {
        return message.c_str();
    }
};
#define CHECK(COND, MESSAGE) ((COND) ? true : throw lisp_error(MESSAGE));

class value;
class closure;
class context;
class cons;

typedef string symbol;
typedef value(*evaluator)(value*, context*);

struct cons {
    value *car;
    cons *cdr;

    cons(value *_car, cons *_cdr): car(_car), cdr(_cdr) {};
    cons(): car(0), cdr(0) {};
    cons(const cons& c): car(c.car), cdr(c.cdr) {};
};

enum val_t {SYMBOL, INT, LIST, CLOSURE};

struct value {
    val_t type;

    union {
        symbol *symb_p;
        int int_v;
        cons *list_p;
        closure *fn_p;
    };

    value(int i): type(INT), int_v(i) {};
    value(symbol *s): type(SYMBOL), symb_p(s) {}; // TODO: INCREF symbol
    value(cons *c): type(LIST), list_p(c) {};

    value(): type(LIST), int_v(0) {};
};

struct closure {
    symbol name;
    virtual value operator()(evaluator, context*, cons*) {return 0;};
};

ostream& operator << (const ostream&, const value&);

#include "l_i.h"
