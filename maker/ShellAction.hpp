#pragma once

#include <string>
#include <vector>


namespace maker {
using std::vector;
using std::string;


class ShellAction {
private:
    const vector<string> _commands;

public:
    ShellAction(const vector<string>& commands);

    void operator()(const string& product,
            const vector<string>& dependencies) const;
};


} // namespace maker
