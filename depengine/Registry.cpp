#include <iostream>
#include <utility>
#include <sstream>
#include <cassert>
#include <regex>

#include "DepException.hpp"
#include "RulePattern.hpp"
#include "Registry.hpp"
#include "Rule.hpp"


namespace depengine
{


void Registry::ProductPublisher::operator()(any product) const
{
    _products[_productName] = product;
}


const Rule& Registry::RuleRetriever::operator()(string productName) const
{
    return _registry.rule(productName);
}


const Rule& Registry::rule(const string& productName)
{
    const auto& location = _rules.find(productName);
    if (location != _rules.end()) {
        return location->second;
    }
    else {
        for (const auto& pattern : _patterns) {
            if (pattern.matches(productName)) {
                const auto result = _rules.emplace(
                    make_pair(
                        productName, pattern.rule(
                            productName, RuleRetriever {*this},
                            ProductPublisher {_products, productName}
                        )));
                assert(result.second);
                return result.first->second;
            }
        }
        stringstream message;
        message << "No rule found for \"" << productName << "\".";
        throw DepException(message.str());
    }
}


void Registry::rule(const RuleDetails& details)
{
    _patterns.emplace_back(details);
}


} // namespace depengine
