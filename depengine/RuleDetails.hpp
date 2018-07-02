#pragma once

#include <boost/any.hpp>
#include <functional>
#include <string>
#include <vector>

#include "Action.hpp"


namespace depengine
{
    using namespace std;
    using boost::any;


    class RuleDetails
    {
    private:
        const string _product;
        const vector<string> _dependencies;
        const Action _action;

    public:
        RuleDetails(
            const string& product,
            const vector<string>& dependencies,
            const Action& action
        );

        const string& getProduct() const;

        const vector<string>& getDependencies() const;

        const Action& getAction() const;

        bool mustExecute() const;

        any execute() const;
    };


} // namespace depengine
