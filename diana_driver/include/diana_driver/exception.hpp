#pragma once

#include <stdexcept>

namespace diana_driver
{
    class DriverException
        : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

}