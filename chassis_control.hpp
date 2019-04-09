#pragma once

#include "evdev.hpp"
#include "gpio.hpp"
#include "types.hpp"

#include <com/inspur/Chassis/Control/Power/server.hpp>
#include <functional>
#include <sdeventplus/event.hpp>
#include <sdeventplus/source/io.hpp>

namespace com
{
namespace inspur
{
namespace chassis
{
using PowerInherit = sdbusplus::server::object_t<
    sdbusplus::com::inspur::Chassis::Control::server::Power>;

class Power : public PowerInherit
{
  public:
    Power(sdbusplus::bus::bus& bus, const char* objPath,
          sdeventplus::Event& event) :
        PowerInherit(bus, objPath),
        event(event), power_out(findGpioDefinition("power_out")),
        pgoodEvdev(findGpioDefinition("pgood"),
                   std::bind(std::mem_fn<bool(bool)>(&Power::pGood), this,
                             std::placeholders::_1),
                   event)
    {
    }

    void powerOn() override;
    void softPowerOff() override;
    void hardPowerOff() override;
    void hardReset() override;

  private:
    sdeventplus::Event& event;

    Gpio power_out;
    Evdev pgoodEvdev;
};
} // namespace chassis
} // namespace inspur
} // namespace com
