#include "treet/build.hpp"
#include <iostream>


void build() {
    using namespace treet::tools;
    using namespace std;


    rule("root", { "file1", "file2" }, {
        "echo 'Root dependencies: $D'",
        "echo 'The first dep is $d'",
        "touch root"
    });


    rule("file1", { "dep" }, {
        "echo 'Making file1'",
        "touch file1"
    });


    rule("dep", [] (auto, auto) {
        cout << "dep done run!"
             << endl;
    });


    rule("file(\\d)", {
        "echo 'Touching!'",
        "touch $p"
    });


    run("root");
}


MAKER_ENTRY(::build)
