#pragma once

#include <functional>
#include <string>
#include <vector>


namespace depengine {
using std::function;
using std::string;
using std::vector;


using Action = function<void(
    const string& product,
    const vector<string>& dependencies
)>;


class RuleDetails {
private:
    const string _product;
    const vector<string> _dependencies;
    const Action _action;

public:
    RuleDetails(
            const string& product,
            const vector<string>& dependencies,
            const Action& action);

    const string& getProduct() const;
    const vector<string>& getDependencies() const;
    const Action& getAction() const;

    bool mustExecute() const;
    void execute() const;
};


} // namespace depengine
