#include "RulePattern.hpp"
#include "Var.hpp"


namespace depengine
{


vector<string> RulePattern::dependencies(
    const string& product
) const
{
    vector<string> filled;
    for (REF depPattern : _depPatterns) {
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
    _prodPattern(details.getProduct()),
    _depPatterns(details.getDependencies()),
    _action(details.getAction())
{
}


bool RulePattern::matches(
    const string& product
) const
{
    return regex_match(product, _prodPattern);
}


Rule RulePattern::rule(
    const string& product,
    const function<const Rule&(string)>& getter,
    const function<void(any)>& setter
) const
{
    return Rule{
        getter, setter, RuleDetails(
            product, dependencies(product), _action
        )
    };
}


} // namespace depengine
