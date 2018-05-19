#include <exception>


class DepException: public std::exception {
private:
    std::string _message;

public:
    DepException(const std::string& message):
        _message(message) { }

    virtual const char* what() const noexcept {
        return _message.c_str();
    }
};
