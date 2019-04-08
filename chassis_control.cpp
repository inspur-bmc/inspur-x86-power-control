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
} // namespace chassis
} // namespace inspur
} // namespace com
