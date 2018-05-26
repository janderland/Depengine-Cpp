#pragma once

#include <string>
#include <vector>


namespace depengine {
using std::string;
using std::vector;


class RuleDetails {
private:
    const string _product;
    const string _command;
    const vector<string> _dependencies;

public:
    RuleDetails(
            string product,
            string command,
            vector<string> dependencies = vector<string>());

    const string& getProduct() const;
    const vector<string>& getDependencies() const;
    bool mustExecute() const;
    void execute() const;
};


} // namespace depengine
