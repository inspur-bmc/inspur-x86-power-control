#pragma once

#include "file.hpp"
#include "types.hpp"

#include <libevdev-1.0/libevdev/libevdev.h>

#include <functional>
#include <memory>
#include <sdeventplus/event.hpp>
#include <sdeventplus/source/io.hpp>
#include <string>

namespace com
{
namespace inspur
{
namespace chassis
{
struct FreeEvDev
{
    void operator()(struct libevdev* device) const
    {
        libevdev_free(device);
    }
};

using EvdevPtr = std::unique_ptr<struct libevdev, FreeEvDev>;

using EvdevCallback = std::function<bool(bool value)>;
class Evdev
{
  public:
    Evdev() = delete;
    Evdev(const Evdev&) = delete;
    Evdev& operator=(const Evdev&) = delete;
    Evdev(Evdev&&) = delete;
    Evdev& operator=(Evdev&&) = delete;

    Evdev(const GpioDefinition& gpiodef, EvdevCallback callback,
          sdeventplus::Event& event) :
        path(std::get<pathField>(gpiodef)),
        key(std::get<keyField>(gpiodef)), callback(callback), event(event),
        fd(openDevice()),
        ioSource(event, fd(), EPOLLIN,
                 std::bind(std::mem_fn(&Evdev::processEvents), this,
                           std::placeholders::_1, std::placeholders::_2,
                           std::placeholders::_3))
    {
    }

  private:
    const std::string path;
    const unsigned int key;
    EvdevCallback callback;
    sdeventplus::Event& event;
    EvdevPtr devicePtr;
    FileDescriptor fd;
    sdeventplus::source::IO ioSource;

    void processEvents(sdeventplus::source::IO& io, int fd, uint32_t revents);

    int openDevice();
};
} // namespace chassis
} // namespace inspur
} // namespace com
