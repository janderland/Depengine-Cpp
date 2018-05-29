#pragma once

#include "RulePattern.hpp"
#include <vector>
#include <string>
#include <list>
#include <map>


namespace depengine {
using std::string;
using std::list;
using std::map;
class RuleDetails;
class Rule;


class Registry {
private:
    map<string, Rule> _rules;
    list<RulePattern> _patterns;

public:
    const Rule& getRule(const string& product);
    void createRule(const RuleDetails& details);
};


} // namespace depengine
