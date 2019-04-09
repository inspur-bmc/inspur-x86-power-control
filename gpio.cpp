#include "gpio.hpp"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdio>
#include <stdexcept>

namespace com
{
namespace inspur
{
namespace chassis
{
int Gpio::requestLine(Value defaultValue)
{
    FileDescriptor fd(open(path.c_str(), 0));
    if (fd() == -1)
    {
        throw std::runtime_error("Failed opening GPIO device");
    }

    gpiohandle_request request{};
    std::snprintf(request.consumer_label, sizeof(request.consumer_label), "%s",
                  label.c_str());

    request.flags = GPIOHANDLE_REQUEST_OUTPUT;
    request.lineoffsets[0] = gpio;
    request.lines = 1;
    request.default_values[0] = static_cast<GpioValue>(defaultValue);
    auto rc = ioctl(fd(), GPIO_GET_LINEHANDLE_IOCTL, &request);
    if (rc == -1)
    {
        throw std::runtime_error("Failed GPIO_GET_LINEHANDLE_IOCTL");
    }
    return request.fd;
}
void Gpio::set(Value value)
{
    gpiohandle_data data{};
    data.values[0] = static_cast<GpioValue>(value);
    auto rc = ioctl(lineFd(), GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    if (rc == -1)
    {
        throw std::runtime_error("Failed GPIOHANDLE_SET_LINE_VALUES_IOCTL");
    }
}

} // namespace chassis
} // namespace inspur
} // namespace com
