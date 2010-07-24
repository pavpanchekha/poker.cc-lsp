//#define TEST_L_P

#pragma once

#include <iostream>
#include <cctype>
#include "l_c.h"
#include "l_i.h"

using std::istream;

cons *parse(istream&);

value parse_val(istream& src) {
    char top = src.peek();
    value ret;
    if (isdigit(top)) {
        int v;
        src >> v;
        ret.type = INT; ret.int_v = v;
    } else if (top == '(') {
        src.get(); // Drop paren
        ret.type = LIST; ret.list_p = parse(src);
        if (src.peek() != ')') cerr << "Unbalanced parentheses (adding in right parenthesis): " << src.peek() << endl;
        else src.get(); // Drop paren
    } else if (top == '\'') {
        src.get();
        ret.type = LIST; ret.list_p = new cons(new value(new symbol("quote")), new cons(new value(parse_val(src)), 0));
    } else {
        symbol *c = new symbol();
        char buf;
        while (!isspace(src.peek()) && src.peek() != ')' && src) {
            src >> buf;
            *c += buf;
        }
        ret.type = SYMBOL; ret.symb_p = c;
    }
    return ret;
}

void swallow_ws(istream& src) {
    while (isspace(src.peek())) {
        src.get();
    }

    if (src.peek() == ';') {
        src.get(); // Semicolon
        while (src && src.peek() != '\n') {
            src.get();
        }
        src.get(); // Newline
    }
}

cons *parse(istream& src) {
    swallow_ws(src);
    cons *head = new cons();
    cons *tail = head;
    while (src && src.peek() != ')') {
        value *vp = new value();
        *vp = parse_val(src);
        cons *c = new cons();
        c->car = vp;
        tail->cdr = c;
        tail = c;
        swallow_ws(src);
    }
    tail->cdr = NULL;
    cons *ret = head->cdr;
    delete head;
    return ret;
}

#ifdef TEST_L_P
#include <sstream>

int main() {
    stringstream s("(/ (- (* 3 4) 5) 6)");
    cout << parse(s) << endl;
}

#endif
