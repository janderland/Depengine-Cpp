#pragma once

#include "DepException.hpp"
#include "RuleDetails.hpp"
#include "Registry.hpp"
#include "Var.hpp"


namespace depengine
{
using boost::any_cast;


class Depengine
{
private:
    Registry _registry;

public:
    void rule(
        const string& product,
        const vector<string>& dependencies,
        const Action& action
    )
    {
        _registry.rule(
            RuleDetails {
                product, dependencies, action
            });
    }

    Rule rule(const string name)
    {
        return _registry.rule(name);
    }

    template<class T> T product(const string& name)
    {
        return _registry.product<T>(name);
    }
};


} // namespace depengine
