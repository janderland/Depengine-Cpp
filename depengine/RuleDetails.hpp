#pragma once

#include <functional>
#include <string>
#include <vector>


namespace depengine {
using std::function;
using std::string;
using std::vector;


class RuleDetails {
private:
    const string _product;
    const vector<string> _dependencies;
    const function<void()> _action;

public:
    RuleDetails(
            string product,
            vector<string> dependencies,
            function<void()> action);

    const string& getProduct() const;
    const vector<string>& getDependencies() const;
    bool mustExecute() const;
    void execute() const;
};


} // namespace depengine
