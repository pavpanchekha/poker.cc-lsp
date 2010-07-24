#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "l_c.cc"
#include "l_e.cc"
#include "l_i.cc"

int main(int argc, char **argv) {
    context *c = mkstdlib();
    ifstream lib_fin("LICENSE.txt");
    eval_all(parse(lib_fin), c);
    lib_fin.close();

    if (argc == 1) {
        string s = "'Welcome-to-my-very-rudimentary-Lisp-interpreter!!!";
        while (cin) {
            stringstream g(s);
            cons *k = parse(g);
            try {
                cout << eval_all(k, c) << endl;
            } catch (lisp_error e) {}
            cout << "?> ";
            getline(cin, s);
        }
    } else {
        ifstream fin(argv[1]);
        cons *k = parse(fin);
        fin.close();
        eval_all(k, c);
        string s = "'Loading-and-running-successful";
        while (cin) {
            stringstream g(s);
            cons *k = parse(g);
            try {
                cout << eval_all(k, c) << endl;
            } catch (lisp_error e) {}
            cout << "?> ";
            getline(cin, s);
        }
    }
}
