#include "diana_hardware/diana_system.hpp"

#include <pluginlib/class_list_macros.hpp>

namespace diana_hardware
{

    CallbackReturn
    DianaSystem::on_init(
        const hardware_interface::HardwareComponentInterfaceParams &params)
    {
        auto result =
            hardware_interface::SystemInterface::on_init(params);

        if (result != CallbackReturn::SUCCESS)
        {
            return result;
        }

        parameters_ =
            HardwareParameters::from_hardware_info(info_);

        const auto dof =
            info_.joints.size();

        position_.assign(dof, 0.0);

        velocity_.assign(dof, 0.0);

        effort_.assign(dof, 0.0);

        command_position_.assign(dof, 0.0);

        command_velocity_.assign(dof, 0.0);

        command_effort_.assign(dof, 0.0);

        driver_ =
            DriverFactory::create(
                parameters_.use_fake_hardware);

        if (!driver_)
        {
            return CallbackReturn::ERROR;
        }

        return driver_->configure(

            info_,

            parameters_,

            position_,

            velocity_,

            effort_,

            command_position_,

            command_velocity_,

            command_effort_);
    }

    CallbackReturn
    DianaSystem::on_configure(
        const rclcpp_lifecycle::State &)
    {
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn
    DianaSystem::on_activate(
        const rclcpp_lifecycle::State &)
    {
        return driver_->activate();
    }

    CallbackReturn
    DianaSystem::on_deactivate(
        const rclcpp_lifecycle::State &)
    {
        return driver_->deactivate();
    }

    std::vector<hardware_interface::StateInterface>
    DianaSystem::export_state_interfaces()
    {
        std::vector<hardware_interface::StateInterface> state_interfaces;

        state_interfaces.reserve(info_.joints.size() * 3);

        for (std::size_t i = 0; i < info_.joints.size(); ++i)
        {
            state_interfaces.emplace_back(
                info_.joints[i].name,
                hardware_interface::HW_IF_POSITION,
                &position_[i]);

            state_interfaces.emplace_back(
                info_.joints[i].name,
                hardware_interface::HW_IF_VELOCITY,
                &velocity_[i]);

            state_interfaces.emplace_back(
                info_.joints[i].name,
                hardware_interface::HW_IF_EFFORT,
                &effort_[i]);
        }

        return state_interfaces;
    }

    std::vector<hardware_interface::CommandInterface>
    DianaSystem::export_command_interfaces()
    {
        std::vector<hardware_interface::CommandInterface> command_interfaces;

        command_interfaces.reserve(info_.joints.size());

        for (std::size_t i = 0; i < info_.joints.size(); ++i)
        {
            command_interfaces.emplace_back(
                info_.joints[i].name,
                hardware_interface::HW_IF_POSITION,
                &command_position_[i]);
        }

        return command_interfaces;
    }

    hardware_interface::return_type
    DianaSystem::read(
        const rclcpp::Time &,
        const rclcpp::Duration &)
    {
        return driver_->read();
    }

    hardware_interface::return_type
    DianaSystem::write(
        const rclcpp::Time &,
        const rclcpp::Duration &)
    {
        return driver_->write();
    }

} // namespace diana_hardware

PLUGINLIB_EXPORT_CLASS(
    diana_hardware::DianaSystem,
    hardware_interface::SystemInterface)