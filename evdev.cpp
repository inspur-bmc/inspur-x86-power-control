#include "evdev.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>

namespace com
{
namespace inspur
{
namespace chassis
{

int Evdev::openDevice()
{
    int fd = open(path.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd < 0)
    {
        throw std::system_error(errno, std::generic_category(), "open device");
    }
    struct libevdev* evdev = nullptr;
    auto rc = libevdev_new_from_fd(fd, &evdev);
    if (rc < 0)
    {
        close(fd);
        throw std::system_error(errno, std::generic_category(), "init evdev");
    }
    devicePtr.reset(evdev);

    int value = 0;
    auto fetch_rc = libevdev_fetch_event_value(evdev, EV_KEY, key, &value);

    if (0 == fetch_rc)
    {
        close(fd);
        throw std::system_error(errno, std::generic_category(), "fetch value");
    }

    callback(value);
    return fd;
}

void Evdev::processEvents(sdeventplus::source::IO&, int, uint32_t)
{
    struct input_event ev
    {
    };

    int rc = 0;
    while (rc >= 0)
    {
        rc = libevdev_next_event(devicePtr.get(), LIBEVDEV_READ_FLAG_NORMAL,
                                 &ev);
        if (rc < 0)
        {
            return;
        }
        if (rc == LIBEVDEV_READ_STATUS_SUCCESS)
        {
            if (ev.type == EV_SYN && ev.code == SYN_REPORT)
            {
                continue;
            }
            if (ev.code == key)
            {
                callback(ev.value);
            }
        }
    }
}

} // namespace chassis
} // namespace inspur
} // namespace com
