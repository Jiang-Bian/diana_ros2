#pragma once

#include <string>

#include <hardware_interface/hardware_info.hpp>

namespace diana_hardware
{

    struct HardwareParameters
    {
        bool use_fake_hardware{true};

        std::string robot_ip;

        uint16_t command_port{1337};

        uint16_t state_port{1338};

        double control_frequency{1000.0};

        static HardwareParameters from_hardware_info(
            const hardware_interface::HardwareInfo &info)
        {
            HardwareParameters params;

            auto find_parameter =
                [&](const std::string &name) -> std::string
            {
                auto iter = info.hardware_parameters.find(name);
                if (iter == info.hardware_parameters.end())
                {
                    return "";
                }
                return iter->second;
            };

            auto value = find_parameter("use_fake_hardware");
            if (!value.empty())
            {
                params.use_fake_hardware =
                    (value == "true" || value == "1");
            }

            value = find_parameter("robot_ip");
            if (!value.empty())
            {
                params.robot_ip = value;
            }

            value = find_parameter("command_port");
            if (!value.empty())
            {
                params.command_port =
                    static_cast<uint16_t>(std::stoi(value));
            }

            value = find_parameter("state_port");
            if (!value.empty())
            {
                params.state_port =
                    static_cast<uint16_t>(std::stoi(value));
            }

            value = find_parameter("control_frequency");
            if (!value.empty())
            {
                params.control_frequency =
                    std::stod(value);
            }

            return params;
        }
    };

} // namespace diana_hardware