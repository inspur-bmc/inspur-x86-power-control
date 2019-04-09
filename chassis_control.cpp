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

void Power::powerOn()
{
}

void Power::softPowerOff()
{
}

void Power::hardPowerOff()
{
    std::cout << "forcePowerOff" << std::endl;
    power_out.set(Gpio::Value::low);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    power_out.set(Gpio::Value::high);
}

void Power::hardReset()
{
}

} // namespace chassis
} // namespace inspur
} // namespace com
