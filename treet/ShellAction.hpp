#pragma once

#include "depengine/Registry.hpp"
#include<boost/any.hpp>
#include <string>
#include <vector>


namespace treet {
using depengine::Registry;
using std::vector;
using std::string;
using boost::any;


class ShellAction {
private:
    const vector<string> _commands;

public:
    ShellAction(const vector<string>& commands);

    any operator()(const string& product,
            const vector<string>& dependencies) const;
};


} // namespace treet
