#include "treet/build.hpp"
#include <iostream>


void build() {
    using namespace treet::tools;
    using namespace std;


    rule("output", { "source1", "source2" }, {
        "echo 'Get all dependencies using $D'",
        "echo 'Get first dependency using $d'",
        "cat $D > root",
    });


    rule("source(\\d)", { "func$1" }, {
        "echo 'Get product using $p'",
        "echo '$p' > $p"
    });


    rule("func(\\d)", [] (auto, auto) {
        cout << "Running a C++ function"
             << endl;
    });


    run("output");
}


MAKER_ENTRY(::build)
