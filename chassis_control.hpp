#pragma once

#include "evdev.hpp"
#include "gpio.hpp"
#include "types.hpp"

#include <com/inspur/Chassis/Control/Power/server.hpp>
#include <functional>
#include <sdeventplus/clock.hpp>
#include <sdeventplus/event.hpp>
#include <sdeventplus/source/io.hpp>
#include <sdeventplus/utility/timer.hpp>

namespace com
{
namespace inspur
{
namespace chassis
{
using PowerInherit = sdbusplus::server::object_t<
    sdbusplus::com::inspur::Chassis::Control::server::Power>;

using Timer = sdeventplus::utility::Timer<sdeventplus::ClockId::RealTime>;
class Power : public PowerInherit
{
  public:
    Power(sdbusplus::bus::bus& bus, const char* objPath,
          sdeventplus::Event& event) :
        PowerInherit(bus, objPath),
        bus(bus), event(event), power_out(findGpioDefinition("power_out")),
        reset_out(findGpioDefinition("reset_out")),
        pgoodEvdev(findGpioDefinition("pgood"),
                   std::bind(std::mem_fn(&Power::pgoodHandle), this,
                             std::placeholders::_1),
                   event),
        resetTimer(event, nullptr), powerTimer(event, nullptr)
    {
    }

    void powerOn() override;
    void softPowerOff() override;
    void hardPowerOff() override;
    void hardReset() override;

  private:
    sdbusplus::bus::bus& bus;
    sdeventplus::Event& event;

    Gpio power_out;
    Gpio reset_out;
    Evdev pgoodEvdev;

    Timer resetTimer;
    Timer powerTimer;

    void startSystemdUnit(const std::string& unit);
    void syncChassisState();
    void pgoodHandle(bool value);
};
} // namespace chassis
} // namespace inspur
} // namespace com
