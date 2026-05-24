SERIAL_DRIVER = vendor
POINTING_DEVICE_DRIVER = pmw3360

SRC += analog.c

SRC += lib/common_killerwhale.c
SRC += lib/add_keycodes.c
SRC += lib/add_oled.c
SRC += lib/add_rgblayers.c

OS_DETECTION_ENABLE = yes
NO_USB_STARTUP_CHECK = yes
WAIT_FOR_USB = yes

JOYSTICK_ENABLE = yes
