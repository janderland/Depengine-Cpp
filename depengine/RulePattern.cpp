#include "RulePattern.hpp"


namespace depengine {


vector<string> RulePattern::dependencies(
  const string& product
) const {
  vector<string> filled;
  for (const auto& depPattern : _depPatterns) {
    filled.emplace_back(
      regex_replace(
        product, _prodPattern, depPattern,
        regex_constants::format_no_copy
      ));
  }
  return filled;
}


RulePattern::RulePattern(
  const RuleDetails& details
):
  _prodPattern(details._product),
  _depPatterns(details._dependencies),
  _action(details._action)
{
}


bool RulePattern::matches(
  const string& product
) const {
  return regex_match(product, _prodPattern);
}


Rule RulePattern::rule(
  const string& product,
  const function<const Rule&(string)>& getter,
  const function<void(any)>& setter
) const {
  return {
    getter, setter, {
      product, dependencies(product), _action
    }
  };
}


} // namespace depengine
