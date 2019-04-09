#pragma once

#include <string>
#include <tuple>

namespace com
{
namespace inspur
{
namespace chassis
{
using GpioDefinition = std::tuple<uint32_t, std::string, std::string>;
constexpr auto keyField = 0;
constexpr auto pathField = 1;
constexpr auto labelField = 2;

const GpioDefinition findGpioDefinition(const std::string& name);

} // namespace chassis
} // namespace inspur
} // namespace com
