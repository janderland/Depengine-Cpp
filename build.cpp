#include "treet/build.hpp"
#include <iostream>

using namespace treet::tools;
using namespace std;

void build() {
  rule("output", {"source1", "source2"}, {
    "echo 'All dependencies: $D'",
    "echo 'First dependency: $d'",
    "cat $D > output",
  });

  rule("source(\\d)", {"func$1"}, {
    "echo 'Product: $p'",
    "echo '$p' > $p",
  });

  rule("func(\\d)", [](auto, auto) {
    cout << "Running a C++ function" << endl;
    TREET_NO_PRODUCT
  });
}

TREET_SETUP(::build)
