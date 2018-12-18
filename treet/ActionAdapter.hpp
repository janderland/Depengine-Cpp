#pragma once

#include <boost/any.hpp>
#include <functional>
#include <string>
#include <vector>

#include "depengine/Action.hpp"


namespace treet {
using namespace depengine;
using namespace boost;
using namespace std;


template<class Func, class... Args>
Action ActionAdapter(Func adaptee, Args... args) {
  return [=](auto, auto) {
    return adaptee(args...);
  };
};


} // namespace treet
