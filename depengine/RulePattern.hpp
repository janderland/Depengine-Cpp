#pragma once

#include <string>
#include <vector>
#include <regex>

#include "RuleDetails.hpp"
#include "Action.hpp"
#include "Rule.hpp"


namespace depengine {
using namespace std;


class RulePattern {
private:
  const regex _prodPattern;
  const vector<string> _depPatterns;
  const Action _action;

  vector<string> dependencies(
    const string& product
  ) const;

public:
  RulePattern(const RuleDetails& details);

  bool matches(const string& product) const;

  Rule rule(
    const string& product,
    const function<const Rule&(string)>& getter,
    const function<void(any)>& setter
  ) const;
};


} // namespace depengine
