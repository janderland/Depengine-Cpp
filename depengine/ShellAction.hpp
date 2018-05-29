#pragma once

#include <string>
#include <vector>


namespace depengine {
using std::vector;
using std::string;


class ShellAction {
private:
    const string _command;

    string replaceCodes(
            const string& product, const vector<string>&) const;

public:
    ShellAction(const string& command);

    void operator()(const string& product,
            const vector<string>& dependencies) const;
};


} // namespace depengine
