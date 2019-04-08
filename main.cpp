#include "config.h"

#include "argument.hpp"
#include "chassis_control.hpp"
#include "evdev.hpp"

#include <iostream>
#include <phosphor-logging/elog-errors.hpp>
#include <phosphor-logging/elog.hpp>
#include <phosphor-logging/log.hpp>
#include <sdbusplus/bus.hpp>
#include <sdeventplus/event.hpp>
#include <xyz/openbmc_project/Common/error.hpp>

using namespace com::inspur::chassis;
int main(int argc, char** argv)
{
    argument::ArgumentParser argumentParser(argc, argv);

    try
    {
        auto objPath = std::string{CHASSIS_OBJPATH} + '0';
        auto bus = sdbusplus::bus::new_default();
        bus.request_name(CHASSIS_BUSNAME);

        auto event = sdeventplus::Event::get_default();
        bus.attach_event(event.get(), SD_EVENT_PRIORITY_NORMAL);

        Power power0(bus, objPath.c_str(), event);
        Evdev pgoodEvdev(argumentParser["pgood_path"],
                         std::stoi(argumentParser["pgood_keycode"]),
                         std::bind(std::mem_fn<bool(bool)>(&Power::pgood),
                                   &power0, std::placeholders::_1),
                         event);
        return event.loop();
    }
    catch (const sdeventplus::SdEventError& e)
    {
        using namespace phosphor::logging;
        using namespace sdbusplus::xyz::openbmc_project::Common::Error;
        log<level::ERR>("Error occurred during the sdeventplus loop",
                        entry("ERROR=%s", e.what()));
        elog<InternalFailure>();
    }
}
