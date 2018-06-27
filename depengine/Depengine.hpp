#pragma once

#include "DepException.hpp"
#include "RuleDetails.hpp"
#include "Registry.hpp"
#include "Var.hpp"


namespace depengine {
using boost::any_cast;


class Depengine {
private:
    Registry _registry;

public:
    void createRule(
            const string& product,
            const vector<string>& dependencies,
            const Action& action) {
        _registry.createRule(
                RuleDetails(
                    product,
                    dependencies,
                    action));
    }

    Rule getRule(const string name) {
        return _registry.getRule(name);
    }

    template<class T>
    T getProduct(const string& name) {
        return _registry.getProduct<T>(name);
    }
};


} // namespace depengine
