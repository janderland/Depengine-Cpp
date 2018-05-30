#include "maker/build.hpp"


void build() {
    using namespace maker::tools;


    rule("root", { "file1", "file2" }, {
        "echo 'Root dependencies: $D'",
        "echo 'The first dep is $d'",
        "touch root"
    });


    rule("file1", {
        "echo 'Making file1'",
        "touch file1"
    });


    rule("file(\\d)", {
        "echo 'Touching!'",
        "touch $p"
    });


    run("root");
}


MAKER_ENTRY(::build)
