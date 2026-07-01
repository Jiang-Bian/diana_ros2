#pragma once

#include "diana_hardware/hardware_driver.hpp"

namespace diana_hardware
{

class FCIHardwareDriver final : public HardwareDriver
{
public:
  FCIHardwareDriver() = default;
  ~FCIHardwareDriver() override = default;

  CallbackReturn configure(
      const hardware_interface::HardwareInfo & info,
      const HardwareParameters & parameters,
      std::vector<double> & position,
      std::vector<double> & velocity,
      std::vector<double> & effort,
      std::vector<double> & command_position,
      std::vector<double> & command_velocity,
      std::vector<double> & command_effort) override;

  CallbackReturn activate() override;

  CallbackReturn deactivate() override;

  hardware_interface::return_type read() override;

  hardware_interface::return_type write() override;

private:
  bool active_{false};

  // Step5 接入 Diana FCI SDK 后替换为真正 Driver
  // std::unique_ptr<DianaDriver> driver_;
};

} // namespace diana_hardware