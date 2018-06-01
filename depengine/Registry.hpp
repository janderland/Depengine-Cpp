#pragma once

#include <vector>
#include <string>
#include <list>
#include <map>

#include "RulePattern.hpp"
#include "RuleDetails.hpp"
#include "boost/any.hpp"
#include "Rule.hpp"


namespace depengine {
using namespace std;
using boost::any;
class Rule;


class Registry {
private:
    map<string, Rule> _rules;
    list<RulePattern> _patterns;
    map<string, any> _products;

public:
    const Rule& getRule(const string& product);
    void createRule(const RuleDetails& details);
    map<string, any>& getProducts();
};


} // namespace depengine
