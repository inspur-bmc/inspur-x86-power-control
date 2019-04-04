#include "chassis_control.hpp"

#include <iostream>

namespace com
{
namespace inspur
{
namespace chassis
{

bool Power::forcePowerOff()
{
    std::cout << "forcePowerOff" << std::endl;
    return true;
}

bool Power::pgood(bool value)
{
    std::cout << "pgood,value = " << value << std::endl;
    return PowerInherit::pgood(value);
}
} // namespace chassis
} // namespace inspur
} // namespace com
