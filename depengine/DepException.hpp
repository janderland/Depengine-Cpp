#pragma once

#include <exception>
#include <string>


namespace depengine
{
using namespace std;


class DepException: public std::exception
{
private:
    const string _message;

public:
    DepException(string message):
        _message(std::move(message))
    {
    }

    const char* what() const noexcept override
    {
        return _message.c_str();
    }
};


} // namespace depengine
