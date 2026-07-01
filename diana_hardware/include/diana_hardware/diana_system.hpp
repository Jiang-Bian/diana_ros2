#pragma once

#include <memory>
#include <vector>

#include <hardware_interface/system_interface.hpp>

#include "diana_hardware/driver_factory.hpp"
#include "diana_hardware/hardware_driver.hpp"
#include "diana_hardware/hardware_parameters.hpp"
#include "diana_hardware/visibility_control.hpp"

namespace diana_hardware
{

    class DianaSystem final
        : public hardware_interface::SystemInterface
    {
    public:
        RCLCPP_SHARED_PTR_DEFINITIONS(DianaSystem)

        DIANA_HARDWARE_PUBLIC
        DianaSystem() = default;

        ~DianaSystem() override = default;

        CallbackReturn on_init(
            const hardware_interface::HardwareComponentInterfaceParams &params) override;

        CallbackReturn on_configure(
            const rclcpp_lifecycle::State &previous_state) override;

        CallbackReturn on_activate(
            const rclcpp_lifecycle::State &previous_state) override;

        CallbackReturn on_deactivate(
            const rclcpp_lifecycle::State &previous_state) override;

        std::vector<hardware_interface::StateInterface>
        export_state_interfaces() override;

        std::vector<hardware_interface::CommandInterface>
        export_command_interfaces() override;

        hardware_interface::return_type read(
            const rclcpp::Time &,
            const rclcpp::Duration &) override;

        hardware_interface::return_type write(
            const rclcpp::Time &,
            const rclcpp::Duration &) override;

    private:
        HardwareParameters parameters_;

        std::unique_ptr<HardwareDriver> driver_;

        std::vector<double> position_;

        std::vector<double> velocity_;

        std::vector<double> effort_;

        std::vector<double> command_position_;

        std::vector<double> command_velocity_;

        std::vector<double> command_effort_;
    };

}