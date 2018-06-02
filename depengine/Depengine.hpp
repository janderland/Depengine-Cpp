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
        REF products = _registry.getProducts();
        auto iter = products.find(name);
        if (iter != products.end()) {
            return any_cast<T>(iter->second);
        }
        else {
            stringstream message;
            message
                << "No product in cache named \""
                << name << "\".";
            throw DepException(message.str());
        }
    }
};


} // namespace depengine
