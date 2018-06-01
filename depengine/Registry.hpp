#pragma once

#include "RulePattern.hpp"
#include "boost/any.hpp"
#include <vector>
#include <string>
#include <list>
#include <map>


namespace depengine {
using namespace std;
using boost::any;
class RuleDetails;
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
