#include <iostream>
#include "Dealer.h"
#include "HandPavel.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int main() {
    srand(time(0));
    HandPavel h("Test", 0);
    Dealer d;

    VC v = d.deal(5);
    sort(v.begin(), v.end());
    h.add(v);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << "(" << v[i].card() << ")" << ", ";
    }
    cout << endl;

    VC v2 = h.discard();
    for (int i = 0; i < v2.size(); i++) {
        cout << v2[i] << "(" << v2[i].card() << ")" << ", ";
    }
    cout << endl;
}
