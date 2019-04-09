sbin_PROGRAMS = inspur-x86-power-control

inspur_x86_power_control_SOURCES = \
	main.cpp \
	argument.cpp \
	chassis_control.cpp \
	evdev.cpp \
	gpio.cpp

inspur_x86_power_control_CXXFLAGS = \
	${SYSTEMD_CFLAGS} \
	${INSPUR_DBUS_INTERFACES_CFLAGS} \
	${PHOSPHOR_DBUS_INTERFACES_CFLAGS} \
	${SDBUSPLUS_CFLAGS} \
	${SDEVENTPLUS_CFLAGS} \
	${PHOSPHOR_LOGGING_CFLAGS} \
	${LIBEVDEV_CFLAGS}
inspur_x86_power_control_LDFLAGS = \
	${SYSTEMD_LIBS} \
	${INSPUR_DBUS_INTERFACES_LIBS} \
	${PHOSPHOR_DBUS_INTERFACES_LIBS} \
	${SDBUSPLUS_LIBS} \
	${SDEVENTPLUS_LIBS} \
	${PHOSPHOR_LOGGING_LIBS} \
	${LIBEVDEV_LIBS}
