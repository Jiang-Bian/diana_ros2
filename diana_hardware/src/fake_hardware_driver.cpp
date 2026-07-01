#include "diana_hardware/fci_hardware_driver.hpp"

namespace diana_hardware
{

    CallbackReturn
    FCIHardwareDriver::configure(
        const hardware_interface::HardwareInfo &info,
        const HardwareParameters &parameters,
        std::vector<double> &position,
        std::vector<double> &velocity,
        std::vector<double> &effort,
        std::vector<double> &command_position,
        std::vector<double> &command_velocity,
        std::vector<double> &command_effort)
    {
        info_ = &info;
        parameters_ = &parameters;

        position_ = &position;
        velocity_ = &velocity;
        effort_ = &effort;

        command_position_ = &command_position;
        command_velocity_ = &command_velocity;
        command_effort_ = &command_effort;

        // Step5:
        // driver_ = std::make_unique<DianaDriver>(parameters.robot_ip);
        // return driver_->connect();

        return CallbackReturn::SUCCESS;
    }

    CallbackReturn
    FCIHardwareDriver::activate()
    {
        active_ = true;

        // Step5:
        // driver_->startRealtime();

        return CallbackReturn::SUCCESS;
    }

    CallbackReturn
    FCIHardwareDriver::deactivate()
    {
        active_ = false;

        // Step5:
        // driver_->stopRealtime();

        return CallbackReturn::SUCCESS;
    }

    hardware_interface::return_type
    FCIHardwareDriver::read()
    {
        if (!active_)
        {
            return hardware_interface::return_type::OK;
        }

        // Step5:
        //
        // driver_->readJointState(
        //      *position_,
        //      *velocity_,
        //      *effort_);

        return hardware_interface::return_type::OK;
    }

    hardware_interface::return_type
    FCIHardwareDriver::write()
    {
        if (!active_)
        {
            return hardware_interface::return_type::OK;
        }

        // Step5:
        //
        // driver_->writeJointCommand(
        //      *command_position_);

        return hardware_interface::return_type::OK;
    }

} // namespace diana_hardware