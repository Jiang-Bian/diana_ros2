#pragma once

#include <memory>

#include "diana_hardware/fake_hardware_driver.hpp"
#include "diana_hardware/fci_hardware_driver.hpp"

namespace diana_hardware
{

    class DriverFactory
    {
    public:
        static std::unique_ptr<HardwareDriver> create(
            bool use_fake_hardware)
        {
            if (use_fake_hardware)
            {
                return std::make_unique<FakeHardwareDriver>();
            }

            return std::make_unique<FCIHardwareDriver>();
        }
    };

} // namespace diana_hardware