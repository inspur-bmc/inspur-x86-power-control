#include "config.h"

#include "argument.hpp"
#include "chassis_control.hpp"

#include <iostream>
#include <phosphor-logging/elog-errors.hpp>
#include <phosphor-logging/log.hpp>
#include <sdbusplus/bus.hpp>
#include <sdeventplus/event.hpp>

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

        com::inspur::chassis::Power power0(bus, objPath.c_str(), event);
        return event.loop();
    }
    catch (const sdeventplus::SdEventError& e)
    {
        using namespace phosphor::logging;
        log<level::ERR>("Error occurred during the sdeventplus loop",
                        entry("ERROR=%s", e.what()));
    }
}
