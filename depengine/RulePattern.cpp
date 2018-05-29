#include "RulePattern.hpp"


namespace depengine {
using std::regex_constants::format_no_copy;


vector<string> RulePattern::getDependencies(
        const string& product) const {
    vector<string> filled;
    for (REF depPattern : _depPatterns) {
        filled.emplace_back(regex_replace(
            product, _prodPattern, depPattern,
            format_no_copy));
    }
    return filled;
}


RulePattern::RulePattern(
        Registry& registry,
        const RuleDetails& details):
    _registry(registry),
    _prodPattern(details.getProduct()),
    _depPatterns(details.getDependencies()),
    _action(details.getAction()) { }


bool RulePattern::matches(
        const string& product) const {
    return regex_match(product, _prodPattern);
}


Rule RulePattern::getRule(
        const string& product) const {
    return Rule(
        _registry,
        RuleDetails(
            product,
            getDependencies(product),
            _action));
}


} // namespace depengine
