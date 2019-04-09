#pragma once

#include "file.hpp"
#include "types.hpp"

#include <linux/gpio.h>

#include <string>
#include <type_traits>

namespace com
{
namespace inspur
{
namespace chassis
{
using GpioNumber =
    std::remove_reference<decltype(gpiohandle_request::lineoffsets[0])>::type;
using GpioValue =
    std::remove_reference<decltype(gpiohandle_data::values[0])>::type;
class Gpio
{
  public:
    enum class Value
    {
        low,
        high
    };

    Gpio() = delete;
    Gpio(const Gpio&) = delete;
    Gpio& operator=(const Gpio&) = delete;
    Gpio(Gpio&&) = delete;
    Gpio& operator=(Gpio&&) = delete;

    Gpio(const GpioDefinition& gpiodef, Value defaultValue = Value::high) :
        path(std::get<pathField>(gpiodef)), gpio(std::get<keyField>(gpiodef)),
        label(std::get<labelField>(gpiodef)), lineFd(requestLine(defaultValue))
    {
    }

    void set(Value value);

  private:
    const std::string path;
    const GpioNumber gpio;
    const std::string label;
    FileDescriptor lineFd;
    int requestLine(Value defaultValue);
};
} // namespace chassis
} // namespace inspur
} // namespace com
