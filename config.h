#ifdef TL_TL
#define PATH \
        "/sys/devices/platform/thinkpad_acpi/leds/tpacpi::thinklight/brightness"
#elif defined(TL_CL)
#define PATH \
        "/sys/class/leds/input3::capslock/brightness"
#elif defined(TL_SB)
#define PATH \
        "/sys/class/leds/tpacpi::standby/brightness"
#elif defined(TL_PW)
#define PATH \
	"/sys/devices/platform/thinkpad_acpi/leds/tpacpi::power/brightness"
#elif defined(TL_WL)
#define PATH \
	"/sys/class/leds/phy0-led/brightness"
#endif
