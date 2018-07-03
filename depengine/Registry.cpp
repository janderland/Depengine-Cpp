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


const Rule& Registry::rule(const string& product)
{
    const auto& location = _rules.find(product);
    if (location != _rules.end()) {
        return location->second;
    }
    else {
        for (const auto& pattern : _patterns) {
            if (pattern.matches(product)) {
                const auto result = _rules.emplace(
                    make_pair(
                        product, pattern.rule(
                            product, RuleRetriever {*this},
                            ProductPublisher {_products, product}
                        )));
                assert(result.second);
                return result.first->second;
            }
        }
        stringstream message;
        message << "No rule found for \"" << product << "\".";
        throw DepException(message.str());
    }
}


void Registry::rule(const RuleDetails& details)
{
    _patterns.emplace_back(details);
}


} // namespace depengine
