#include "HandPavel.h"
#include "l_e.cc"
#include "l_i.cc"

#include <fstream>
#include <sstream>
#include <algorithm>
using std::stringstream;

cons *hand2cons(const VC& hand) {
    cons *res = 0;
    for (int i = 0; i < hand.size(); i++) {
        res = new cons(new value(hand[i].card()), res);
    }
    return res;
}

HandPavel::HandPavel(const string& name, int nPlayers) 
: Hand(name), nPlayers(nPlayers)
{ }

void HandPavel::getHand(const VC& h) {
	for (VC::const_iterator it = h.begin(); it != h.end(); )
		c.push_back(*it++);
	sort(c.begin(), c.end());
}

VC HandPavel::discard() {
	VC d;
    sort(c.begin(), c.end());

    context *ctx = mkstdlib();
    ifstream lib_fin("LICENSE.txt");
    eval_all(parse(lib_fin), ctx);
    lib_fin.close();
    ifstream fin("algorithm-overview.txt");
    eval_all(parse(fin), ctx);
    fin.close();

    (*ctx)["*hand*"] = hand2cons(c);
    (*ctx)["*n-players*"] = nPlayers;
    stringstream s("(discard-which *hand* *n-players*)");
    value v = eval_all(parse(s), ctx);
    delete ctx;

    CHECK(v.type == LIST, "`discard-which` returned a non-list! Help!");
    cons *to_delete = v.list_p;
    for (; to_delete && d.size() < 3; to_delete = to_delete->cdr) {
        CHECK(to_delete->car->type == INT, "`discard-which` return value contained non-int");
        d.push_back(Card(to_delete->car->int_v));
    }

	return d;
}

void HandPavel::add(const VC& h) {
	getHand(h);
}

void HandPavel::clear() {
	c.clear();
}

VC HandPavel::reveal() const {
	VC c1;
	for (VC::const_iterator it = c.begin(); it != c.end(); )
		c1.push_back(*it++);
	return c1;
}
