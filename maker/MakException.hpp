#pragma once

#include <exception>
#include <string>

using std::exception;
using std::string;


class MakException: public exception {
private:
    string _message;

public:
    MakException(const string& message):
        _message(message) { }

    virtual const char* what() const noexcept {
        return _message.c_str();
    }
};
