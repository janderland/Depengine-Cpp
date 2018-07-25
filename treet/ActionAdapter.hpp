//
// Created by Jon Anderson on 7/2/18.
//

#ifndef TREET_ACTIONADAPTER_HPP
#define TREET_ACTIONADAPTER_HPP

#include "depengine/Action.hpp"
#include <boost/any.hpp>
#include <functional>
#include <string>
#include <vector>


namespace treet
{
using namespace depengine;
using namespace boost;
using namespace std;


template<class Func, class... Args>
Action ActionAdapter(
    Func adaptee,
    Args... args
)
{
    return [=](
        auto,
        auto
    ) {
        return adaptee(args...);
    };
};


} // namespace treet


#endif //TREET_ACTIONADAPTER_HPP
