#include "chassis_control.hpp"

#include <chrono>
#include <thread>

namespace com
{
namespace inspur
{
namespace chassis
{

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

} // namespace chassis
} // namespace inspur
} // namespace com
