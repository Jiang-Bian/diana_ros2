#pragma once

#include <string>

#include "robot_state.hpp"
#include "robot_command.hpp"

namespace diana_driver
{
    class Driver
    {
    public:
        Driver() = default;

        virtual ~Driver() = default;

        virtual bool connect(
            const std::string &robot_ip) = 0;

        virtual bool disconnect() = 0;

        virtual bool start() = 0;

        virtual bool stop() = 0;

        virtual bool read(
            RobotState &state) = 0;

        virtual bool write(
            const RobotCommand &command) = 0;
    };

}