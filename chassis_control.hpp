#pragma once

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
        event(event)
    {
    }

    bool forcePowerOff() override;

  private:
    sdeventplus::Event& event;
};
} // namespace chassis
} // namespace inspur
} // namespace com
