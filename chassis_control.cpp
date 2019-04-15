#include "chassis_control.hpp"

#include <chrono>
#include <iostream>
#include <thread>

namespace com
{
namespace inspur
{
namespace chassis
{

constexpr auto CHASSIS_STATE_POWEROFF_TGT = "obmc-chassis-poweroff@0.target";
constexpr auto CHASSIS_STATE_POWERON_TGT = "obmc-chassis-poweron@0.target";
constexpr auto HOST_STATE_POWEROFF_TGT = "obmc-host-stop@0.target";
constexpr auto HOST_STATE_POWERON_MIN_TGT = "obmc-host-startmin@0.target";

constexpr auto SYSTEMD_SERVICE = "org.freedesktop.systemd1";
constexpr auto SYSTEMD_OBJ_PATH = "/org/freedesktop/systemd1";
constexpr auto SYSTEMD_INTERFACE = "org.freedesktop.systemd1.Manager";

void Power::powerOn()
{
    power_out.set(Gpio::Value::low);
    auto cb = [&](Timer& timer) {
        std::cout << "pwerOn timer cb" << std::endl;
        power_out.set(Gpio::Value::high);
    };
    powerTimer.set_callback(std::move(cb));
    powerTimer.restartOnce(std::chrono::milliseconds(300));
}

void Power::softPowerOff()
{
    power_out.set(Gpio::Value::low);
    auto cb = [&](Timer& timer) {
        std::cout << "softPowerOff timer cb" << std::endl;
        power_out.set(Gpio::Value::high);
    };
    powerTimer.set_callback(std::move(cb));
    powerTimer.restartOnce(std::chrono::seconds(3));
}

void Power::hardPowerOff()
{
    power_out.set(Gpio::Value::low);
    auto cb = [&](Timer& timer) {
        std::cout << "hardPowerOff timer cb" << std::endl;
        power_out.set(Gpio::Value::high);
    };
    powerTimer.set_callback(std::move(cb));
    powerTimer.restartOnce(std::chrono::seconds(6));
}

void Power::hardReset()
{
    reset_out.set(Gpio::Value::low);
    auto cb = [&](Timer& timer) {
        std::cout << "hardReset timer cb" << std::endl;
        reset_out.set(Gpio::Value::high);
    };
    resetTimer.set_callback(std::move(cb));
    resetTimer.restartOnce(std::chrono::milliseconds(300));
}

void Power::startSystemdUnit(const std::string& unit)
{
    auto method = bus.new_method_call(SYSTEMD_SERVICE, SYSTEMD_OBJ_PATH,
                                      SYSTEMD_INTERFACE, "StartUnit");
    method.append(unit);
    method.append("replace");

    bus.call_noreply(method);
    return;
}

void Power::syncChassisState()
{
    if (pGood())
    {
        startSystemdUnit(CHASSIS_STATE_POWERON_TGT);
        startSystemdUnit(HOST_STATE_POWERON_MIN_TGT);
    }
    else
    {
        startSystemdUnit(CHASSIS_STATE_POWEROFF_TGT);
        startSystemdUnit(HOST_STATE_POWEROFF_TGT);
    }
}

void Power::pgoodHandle(bool value)
{
    PowerInherit::pGood(value);
    syncChassisState();
}

} // namespace chassis
} // namespace inspur
} // namespace com
