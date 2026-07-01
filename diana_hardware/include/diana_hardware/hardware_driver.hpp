#pragma once

#include <vector>

#include <hardware_interface/hardware_info.hpp>
#include <hardware_interface/types/hardware_interface_return_values.hpp>
#include <rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp>
#include <rclcpp_lifecycle/state.hpp>

#include "diana_hardware/hardware_parameters.hpp"

namespace diana_hardware
{

    using CallbackReturn =
        rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

        class HardwareDriver
    {
    public:
        virtual ~HardwareDriver() = default;

        virtual CallbackReturn configure(
            const hardware_interface::HardwareInfo &info,
            const HardwareParameters &parameters,
            std::vector<double> &position,
            std::vector<double> &velocity,
            std::vector<double> &effort,
            std::vector<double> &command_position,
            std::vector<double> &command_velocity,
            std::vector<double> &command_effort) = 0;

        virtual CallbackReturn activate() = 0;

        virtual CallbackReturn deactivate() = 0;

        virtual hardware_interface::return_type read() = 0;

        virtual hardware_interface::return_type write() = 0;

    protected:
        const hardware_interface::HardwareInfo *info_{nullptr};

        const HardwareParameters *parameters_{nullptr};

        std::vector<double> *position_{nullptr};

        std::vector<double> *velocity_{nullptr};

        std::vector<double> *effort_{nullptr};

        std::vector<double> *command_position_{nullptr};

        std::vector<double> *command_velocity_{nullptr};

        std::vector<double> *command_effort_{nullptr};
    };

} // namespace diana_hardware