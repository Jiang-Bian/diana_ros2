#pragma once

#include <array>

namespace diana_driver
{
    struct RobotCommand
    {
        std::array<double, 7> q{};
        std::array<double, 7> dq{};
        std::array<double, 7> tau{};
    };

}