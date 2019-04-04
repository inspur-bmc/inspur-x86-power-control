#pragma once

#include <com/inspur/Chassis/Control/Power/server.hpp>
#include <iostream>
#include <sdeventplus/event.hpp>

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
        event(event)
    {
    }

    bool forcePowerOff() override;

    bool pgood(bool value) override;

  private:
    sdeventplus::Event& event;
};
} // namespace chassis
} // namespace inspur
} // namespace com
