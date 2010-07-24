#pragma once

#include "l_p.cc"
#include "l_c.cc"

#define BINOP(OP, NAME) \
    struct f_##NAME: public closure { \
        virtual value operator () (evaluator eval, context *ctx, cons *args) { \
            value k = eval(args->car, ctx); \
            CHECK(k.type == INT, "Cannot apply operator `" #NAME "` to non-ints"); \
            int res = k.int_v; \
            args = args->cdr; \
            for (; args; args = args->cdr) { \
                k = eval(args->car, ctx); \
                CHECK(k.type == INT, "Cannot apply operator `" #NAME "` to non-ints"); \
                res = res OP k.int_v; \
            } \
            value v; \
            v.type = INT; \
            v.int_v = res; \
            return v; \
        } \
    };

#define RELOP(OP, NAME) \
    struct f_##NAME: public closure { \
        virtual value operator () (evaluator eval, context *ctx, cons *args) { \
            value k = eval(args->car, ctx); \
            CHECK(k.type == INT, "Cannot apply operator `" #NAME "` to non-ints"); \
            int last = k.int_v; \
            bool res = true; \
            args = args->cdr; \
            for (; args; args = args->cdr) { \
                k = eval(args->car, ctx); \
                CHECK(k.type == INT, "Cannot apply operator `" #NAME "` to non-ints"); \
                res = last OP k.int_v; \
                last = k.int_v; \
            } \
            value v; \
            v.type = INT; \
            v.int_v = res; \
            return v; \
        } \
    };

#define SAVE(VAR, NAME) \
    f_##NAME *NAME##_inst(new f_##NAME()); \
    value NAME##_v; \
    NAME##_inst->name = VAR; \
    NAME##_v.type = CLOSURE; \
    NAME##_v.fn_p = NAME##_inst; \
    (*stdlib)[VAR] = NAME##_v;

#define FN(NAME, BODY) \
    struct f_##NAME: public closure { \
        virtual value operator () (evaluator eval, context *ctx, cons *args) { \
            BODY \
        } \
    };

bool value2bool(const value& v) {
    switch (v.type) {
        case INT:
            return v.int_v;
        case SYMBOL:
            return v.symb_p->size();
        case CLOSURE:
            return false;
        case LIST:
            return v.list_p;
    }
}

using namespace std;

BINOP(+, add);
BINOP(-, sub);
BINOP(*, mul);
BINOP(/, div);
BINOP(%, mod);

RELOP(==, equals);
RELOP(!=, nequals);
RELOP(<=, ltequals);
RELOP(>=, gtequals);
RELOP(<, lt);
RELOP(>, gt);

FN(quote,
    return *(args->car);
  );

FN(block,
    for (; args->cdr; args = args->cdr) {
        eval(args->car, ctx);
    }
    return eval(args->car, ctx);
  );

FN(list,
    cons *k = new cons();
    cons *end = k;
    for (; args; args = args->cdr) {
        end->cdr = new cons();
        end = end->cdr;
        end->car = new value(eval(args->car, ctx));
    }
    end = k->cdr;
    delete k;
    return end;
  );

FN(cons,
    value a = eval(args->car, ctx);
    value b = eval(args->cdr->car, ctx);
    CHECK(b.type == LIST, "Second argument of `cons` must be a list");
    return new cons(new value(a), b.list_p);
  );

FN(car,
    value k = eval(args->car, ctx);
    CHECK(k.type == LIST, "`car` applied to non-list");
    CHECK(k.list_p, "`car` applied to nil");
    return *(k.list_p->car);
  );

FN(cdr,
    value k = eval(args->car, ctx);
    CHECK(k.type == LIST, "`cdr` applied to non-list");
    CHECK(k.list_p, "`cdr` applied to nil");
    return k.list_p->cdr;
  );

FN(atom,
    value k = eval(args->car, ctx);
    return k.type != LIST;
  );

FN(set,
    CHECK(args->car->type == SYMBOL, "Attempted to `set!` a non-identifier");
    value v = eval(args->cdr->car, ctx);
    if (v.type == CLOSURE) v.fn_p->name = *(args->car->symb_p);
    return (*ctx)[*(args->car->symb_p)] = v;
  );

FN(print,
    for (; args->cdr; args = args->cdr) {
        cout << eval(args->car, ctx) << " ";
    }
    value k = eval(args->car, ctx);
    cout << k << endl;
    return k;
  );

FN(eval,
    return eval(&eval(args->car, ctx), ctx);
  );

struct actual_closure: public closure {
    actual_closure(value *_body, context *_ctx, cons *_args):
        body(_body), ctx(_ctx), args(_args) {
            for(; _args; _args = _args->cdr) {
                CHECK(_args->car->type == SYMBOL, "Parameter list contained non-identifier");
            }
        };

    value operator () (evaluator eval, context *_ctx, cons *_args) {
        map<symbol, value> *m = new map<symbol, value>();
        for (cons *args_p = _args, *bind_p = args;
                args_p && bind_p;
                args_p = args_p->cdr, bind_p = bind_p->cdr) {
            value k = eval(args_p->car, _ctx);
            (*m)[*(bind_p->car->symb_p)] = k;
        }
        context *new_ctx = new context(*m, ctx);
        value k = eval(body, new_ctx);
        delete m;

        return k;
    }

    private:
        value *body;
        context *ctx;
        cons *args;
};

struct actual_fexpr: public closure {
    actual_fexpr(value *_body, context *_ctx, cons *_args):
        body(_body), ctx(_ctx), args(_args) {
            for(; _args; _args = _args->cdr) {
                CHECK(_args->car->type == SYMBOL, "Parameter list contained a non-identifier");
            }
        };
    value operator () (evaluator eval, context *_ctx, cons *_args) {
        map<symbol, value> *m = new map<symbol, value>();
        for (cons *args_p = _args, *bind_p = args;
                args_p && bind_p;
                args_p = args_p->cdr, bind_p = bind_p->cdr) {
            (*m)[*(bind_p->car->symb_p)] = *(args_p->car);
        }
        context *new_ctx = new context(*m, ctx);
        value k = eval(body, new_ctx);
        delete new_ctx;
        delete m;

        return k;
    }

    private:
        value *body;
        context *ctx;
        cons *args;
};

FN(fn,
    CHECK(args->car->type == LIST, "Parameter specification not a list");
    actual_closure* c = new actual_closure(new value(new cons(new value(new symbol("block")), args->cdr)), ctx, args->car->list_p);
    value v;
    v.type = CLOSURE;
    v.fn_p = c;
    return v;
  );

FN(fx,
    CHECK(args->car->type == LIST, "Parameter specification not a list");
    actual_fexpr* c = new actual_fexpr(new value(new cons(new value(new symbol("block")), args->cdr)), ctx, args->car->list_p);
    value v;
    v.type = CLOSURE;
    v.fn_p = c;
    return v;
  );

FN(if_,
    value v = eval(args->car, ctx);
    if (value2bool(v)) {
        return eval(args->cdr->car, ctx);
    } else if (args->cdr->cdr) {
        return eval(args->cdr->cdr->car, ctx);
    } else {
        return value();
    }
  );

FN(not_,
    return !value2bool(eval(args->car, ctx));
  );

context *mkstdlib() {
    context *stdlib = new context(*new map<symbol, value>);
    SAVE("+",  add);
    SAVE("-",  sub);
    SAVE("*",  mul);
    SAVE("/",  div);
    SAVE("%",  mod);
    SAVE("=",  equals);
    SAVE("!=", nequals);
    SAVE("<",  lt);
    SAVE(">",  gt);
    SAVE("<=", ltequals);
    SAVE(">=", gtequals);

    SAVE("block", block);
    SAVE("quote", quote);
    SAVE("cons",  cons);
    SAVE("car",   car);
    SAVE("cdr",   cdr);
    SAVE("atom?", atom);
    SAVE("set!",  set);
    SAVE("print", print);
    SAVE("eval",  eval);
    SAVE("fn",    fn);
    SAVE("if",    if_);
    SAVE("not",   not_);
    SAVE("fx",    fx);
    SAVE("list",  list);
    return stdlib;
}
