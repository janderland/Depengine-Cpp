#pragma once

#include <boost/any.hpp>
#include <functional>
#include <string>
#include <vector>


namespace depengine {
using namespace std;
using boost::any;


using Action = function<any(
    const string& product,
    const vector<string>& dependencies
)>;


} // namespace depengine
