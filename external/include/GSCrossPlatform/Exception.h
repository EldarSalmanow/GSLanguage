#ifndef GSCROSSPLATFORM_EXCEPTION_H
#define GSCROSSPLATFORM_EXCEPTION_H

#include <GSCrossPlatform/UString.h>

class Exception : public std::exception {
public:

    explicit Exception(UString string)
            : _string(std::move(string)), _utf8String(_string.as_utf8()) {}

public:

    inline constexpr UString Message() const {
        return _string;
    }

public:

    const char *what() const override {
        return _utf8String.c_str();
    }

private:

    UString _string;

    std::string _utf8String;
};

#endif //GSCROSSPLATFORM_EXCEPTION_H
