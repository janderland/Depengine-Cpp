#pragma once

#include <vector>
#include <string>
#include <list>
#include <map>

#include "DepException.hpp"
#include "RulePattern.hpp"
#include "RuleDetails.hpp"
#include "boost/any.hpp"
#include "Rule.hpp"


namespace depengine
{
using namespace boost;
using namespace std;


class Registry
{
private:
    map<string, Rule> _rules;
    list<RulePattern> _patterns;
    map<string, any> _products;

    struct ProductPublisher
    {
        map<string, any>& _products;
        const string _productName;

        void operator()(any product) const;
    };

    struct RuleRetriever
    {
        Registry& _registry;

        const Rule& operator()(string productName) const;
    };

public:
    const Rule& rule(const string& product);

    void rule(const RuleDetails& details);

    template<class T> T product(const string& name)
    {
        auto iter = _products.find(name);
        if (iter != _products.end()) {
            return any_cast<T>(iter->second);
        }
        else {
            stringstream message;
            message << "No product in cache named \"" << name << "\".";
            throw DepException(message.str());
        }
    }
};


} // namespace depengine
