#pragma once

#include <boost/any.hpp>
#include <functional>
#include <string>
#include <vector>

#include "Action.hpp"


namespace depengine
{
    using namespace boost;
    using namespace std;


    class RuleDetails
    {
    public:
        const string _product;
        const vector<string> _dependencies;
        const Action _action;

        const string& getProduct() const;

        const vector<string>& getDependencies() const;

        const Action& getAction() const;

        bool mustExecute() const;

        any execute() const;
    };


} // namespace depengine
