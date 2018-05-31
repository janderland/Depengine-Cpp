#include "treet/build.hpp"
#include <iostream>


void build() {
    using namespace treet::tools;
    using namespace std;


    rule("output", { "source1", "source2" }, {
        "echo 'All dependencies: $D'",
        "echo 'First dependency: $d'",
        "cat $D > output",
    });


    rule("source(\\d)", { "func$1" }, {
        "echo 'Product: $p'",
        "echo '$p' > $p"
    });


    rule("func(\\d)", [] (auto, auto) {
        cout << "Running a C++ function"
             << endl;
    });


    run("output");
}


MAKER_ENTRY(::build)
