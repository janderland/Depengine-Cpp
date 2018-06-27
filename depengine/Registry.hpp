#pragma once

#include <vector>
#include <string>
#include <list>
#include <map>

#include "DepException.hpp"
#include "RulePattern.hpp"
#include "RuleDetails.hpp"
#include "boost/any.hpp"
#include "Rule.hpp"


namespace depengine {
using namespace boost;
using namespace std;
class Rule;


class Registry {
private:
    map<string, Rule> _rules;
    list<RulePattern> _patterns;
    map<string, any> _products;

public:
    const Rule& getRule(const string& product);
    void createRule(const RuleDetails& details);

    template<class T> T getProduct(const string& name) {
        auto iter = _products.find(name);
        if (iter != _products.end()) {
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
