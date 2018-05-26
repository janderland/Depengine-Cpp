#pragma once

#include <vector>
#include <string>
#include <map>


namespace depengine {
using std::string;
using std::map;
class RuleDetails;
class Rule;


class Registry {
private:
    map<string, Rule> rules;

public:
    const Rule& getRule(const string& product) const;
    void createRule(RuleDetails&& details);
};


} // namespace depengine
