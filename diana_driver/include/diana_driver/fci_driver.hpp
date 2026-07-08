#pragma once

#include "diana_driver/driver.hpp"

namespace diana_driver
{

    class FCIDriver final : public Driver
    {
    public:
        FCIDriver();

        ~FCIDriver() override;

        bool connect(
            const std::string &robot_ip) override;

        bool disconnect() override;

        bool start() override;

        bool stop() override;

        bool read(
            RobotState &state) override;

        bool write(
            const RobotCommand &command) override;

    private:
        std::string robot_ip_;

        bool connected_{false};

        bool running_{false};

        RobotState state_;
    };

} // namespace diana_driver