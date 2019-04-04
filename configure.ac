# Initialization
AC_PREREQ([2.69])
AC_INIT([inspur-x86-power-control], [0.1])
AC_LANG([C++])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign dist-xz])
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL

PKG_CHECK_MODULES([INSPUR_DBUS_INTERFACES], [inspur-dbus-interfaces])
PKG_CHECK_MODULES([SDBUSPLUS], [sdbusplus])
PKG_CHECK_MODULES([SDEVENTPLUS], [sdeventplus])
PKG_CHECK_MODULES([PHOSPHOR_LOGGING], [phosphor-logging])

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_17([noext])
AX_APPEND_COMPILE_FLAGS([-Wall -Werror], [CXXFLAGS])

# For libtools
LT_INIT
AC_ARG_VAR(CHASSIS_BUSNAME, [The chassis Dbus busname to own])
AS_IF([test "x$CHASSIS_BUSNAME" == "x"], [CHASSIS_BUSNAME="com.inspur.chassis.power"])
AC_DEFINE_UNQUOTED([CHASSIS_BUSNAME], ["$CHASSIS_BUSNAME"], [The chassis DBus busname to own])

AC_ARG_VAR(CHASSIS_OBJPATH, [The chassis state manager Dbus root])
AS_IF([test "x$CHASSIS_OBJPATH" == "x"], [CHASSIS_OBJPATH="/com/inspur/chassis/power/chassis"])
AC_DEFINE_UNQUOTED([CHASSIS_OBJPATH], ["$CHASSIS_OBJPATH"], [The chassis state manager Dbus root])


# Create configured output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
