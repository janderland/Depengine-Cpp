#include <iostream>
#include <utility>
#include <sstream>
#include <cassert>
#include <regex>

#include "DepException.hpp"
#include "RulePattern.hpp"
#include "Registry.hpp"
#include "Rule.hpp"
#include "Var.hpp"


namespace depengine
{


void Registry::Setter::operator()(any product) const
{
    _products[_productName] = product;
}


const Rule& Registry::Getter::operator()(string productName) const
{
    return _registry.getRule(productName);
}


const Rule& Registry::getRule(const string& product)
{
    REF location = _rules.find(product);
    if (location != _rules.end()) {
        return location->second;
    }
    else {
        for (REF pattern : _patterns) {
            if (pattern.matches(product)) {
                VAL result = _rules.emplace(
                    make_pair(
                        product, pattern.getRule(
                            product,
                            Getter{*this},
                            Setter{_products, product}
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


void Registry::createRule(const RuleDetails& details)
{
    _patterns.emplace_back(details);
}


} // namespace depengine
