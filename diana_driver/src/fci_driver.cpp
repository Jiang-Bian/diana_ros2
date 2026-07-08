#include "diana_driver/fci_driver.hpp"

namespace diana_driver
{

    FCIDriver::FCIDriver() = default;
    FCIDriver::~FCIDriver() = default;

    bool FCIDriver::connect(
        const std::string &robot_ip)
    {
        robot_ip_ = robot_ip;
        connected_ = true;

        return true;
    }

    bool FCIDriver::disconnect()
    {
        running_ = false;

        connected_ = false;

        return true;
    }

    bool FCIDriver::start()
    {
        if (!connected_)
        {
            return false;
        }

        running_ = true;

        return true;
    }

    bool FCIDriver::stop()
    {
        running_ = false;

        return true;
    }

    bool FCIDriver::read(
        RobotState &state)
    {
        if (!running_)
        {
            return false;
        }

        state = state_;

        return true;
    }

    bool FCIDriver::write(
        const RobotCommand &command)
    {
        if (!running_)
        {
            return false;
        }

        state_.q = command.q;

        state_.dq = command.dq;

        state_.tau = command.tau;

        return true;
    }

}