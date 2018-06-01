#pragma once

#include "Action.hpp"
#include <string>
#include <vector>
#include <regex>


namespace depengine {
using namespace std;
class RuleDetails;
class Registry;
class Rule;


class RulePattern {
private:
    Registry& _registry;
    const regex _prodPattern;
    const vector<string> _depPatterns;
    const Action _action;

    vector<string> getDependencies(
            const string& product) const;

public:
    RulePattern(
            Registry& registry,
            const RuleDetails& details);

    bool matches(const string& product) const;
    Rule getRule(const string& product) const;
};


} // namespace depengine
