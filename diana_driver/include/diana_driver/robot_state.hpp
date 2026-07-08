#pragma once

#include <array>

namespace diana_driver
{

    struct RobotState
    {
        std::array<double, 7> q{};
        std::array<double, 7> dq{};
        std::array<double, 7> tau{};
        std::array<double, 16> tcp_pose{};
    };

}