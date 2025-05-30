# Killer Whale SIDE Unit Trackball LEFT Side Build Manual （[See RIGHT Side there](../rightside/3_SIDE_TRACKBALL.md)）

1. [Start Page](../README_EN.md)
2. [BASE Unit](../leftside/2_BASE.md)
3. SIDE Unit
   - Trackball LEFT Side
   - [D-PAD](../leftside/3_SIDE_DPAD.md)
   - [Wheel (sold separately)](../leftside/3_SIDE_WHEEL.md)
   - [Joystick (sold separately)](../leftside/3_SIDE_JOYSTICK.md)
4.  [TOP Unit](../leftside/4_TOP.md)
5. [ADD Unit](../leftside/5_ADD.md)
6. [Assemble](../leftside/6_ASSEMBLE.md)
7. [Customizations](../leftside/7_CUSTOM.md)
8. [Misc](../leftside/8_MISC.md)

## Contents
![](../img/3_1_trackball_l/3_1_1_contents.jpg)
||types|quantities||
|-|-|-|-|
|1|Mainboard|1|FR4|
|2|Switch plate|1|FR4|
|3|Cover plate|1|Acrylic|
|4|M2 short screws|2|4mm|
|5|M2 middle screws|2|6mm|
|6|M2 long screws|3|10mm|
|7|M3 screws|3|10mm|
|8|M2 nuts|3|
|9|M3 square nuts|3||
|10|M2 long spacers|2|7mm or 8mm|
|11|Bearing|3|2x6x2.5|
|12|Capacitor C3|1|4.7uF|
|13|Capacitor C1, C2|2|10uF|
|14|Regulator|1|UT7500L-18|
|15|MX Switch Socket|2||
|16|Diodes|4|1N4148|
|17|Sensor & lens|1|PMW3360|
|18|Pin header|1||

The following 3D printed parts are also used.
![](../img/3_1_trackball_r/IMG_3411.jpg)

## Soldering
Keep in mind that components will be placed on both sides of the unit.
![](../img/3_1_trackball_l/3_1_2_overall.jpg)
The PCB side with text in Japanese is the back side.
### Soldering of the LEDs (optional)
Solder the 3 LEDs. The round LED should be facing away from the side where soldering is done.
![](../img/3_1_trackball_l/3_1_3_led.jpg)


### Soldering of MX hotswap socket (back side)
From the back side of the unit, solder the MX hotswap sockets while keeping them in place with tweezers.

![](../img/3_1_trackball_l/3_1_4_mxsocket.jpg)

### Soldering of the diodes (back side)
Diodes are directional components. Make sure to align the lines with markings on the PCB.
![](../img/c_diode.jpg)
Insert the diodes in the 4 locations on the back side of the PCB, and solder from the front side of the PCB, and cut the diode legs.
![](../img/3_1_trackball_l/3_1_5_diodes.jpg)


### Soldering of sensor, regulator, capacitors (back side)

Align the round mark on the PCB with the round mark on the chip and solder from the front side.
> [!NOTE]
> As a precaution, do not remove the protecting tape from the sensor yet.

![](../img/3_1_trackball_l/3_1_6_pmw3360.jpg)



Solder the capacitors. The locations C1 and C2 correspond to capacitors with 106 written on them, while C3 correspond to the capacitor with 475 written on it.
![](../img/3_1_trackball_l/3_1_7_c_1.jpg)
![](../img/3_1_trackball_l/3_1_8_c_2.jpg)

Insert the regulator pins from the back side and bend them so that the component is lying on the designated markings on the PCB, then solder.
![](../img/3_1_trackball_l/3_1_9_reg.jpg)

### Soldering of pin headers (back side)
Cut out four sets of 6 pins from the 40 pin headers.

![](../img/c_pin_header_6.jpg)
Insert the pin headers from the back side and solder.
> [!WARNING]
> Insert the long side of the pins. In case you did it the other way around, cut the long side in order to match the length of the short side.

![](../img/3_1_trackball_l/3_1_10_pin_header.jpg)

### Soldering of OLED Display (optional, front side)
If you want to make the OLED module removable, solder a 4pin socket on the surface.
![](../img/3_1_trackball_l/3_1_11_oled_socket.jpg)

Solder the pin headers to the OLED module.
![](../img/c_oled_header.jpg)
If the OLED module is to be soldered directly, solder it to the main board at this time.


## Intermediate assembly and soldering of sockets

### Assembling the switch plate

If the switch plate is tagged, fold it and then sand it.
![](../img/c_switch_r.jpg)
Attach the M2 long spacers and M2 short screws to the switch plate.
> [!NOTE]
> The switch plate has an orientation (lower and top part).

![](../img/3_1_trackball_l/3_1_15_switch_1.jpg)

Attach the cover plate to the spacers with M2 middle screws.
![](../img/3_1_trackball_l/3_1_16_switch_2.jpg)

### Assembling the trackball

Remove the protective film from the sensor and insert the lens.
> [!IMPORTANT]
> The lens has a specific mounting direction, therefore make sure not to apply too much force in case it does not fit well, and check direction instead.

![](../img/3_1_trackball_l/3_1_23_lens_1.jpg)
Heat the lens legs on the back side with a soldering iron to fix them in place.
![](../img/3_1_trackball_l/3_1_24_lens_2.jpg)


Fix the bearings in three places on the ball case prop with three screws and three nuts.
![](../img/3_1_trackball_r/IMG_3361.jpg)

Place the arms on the PCB, put a square nut in the slits, and screw them from the back side.

> [!NOTE]
> Place one arm in the bottom side, and two in the upper side, so as to form an equilateral triangle.

![](../img/3_1_trackball_r/IMG_3367.jpg)

### Connecting to the BASE unit
If this is the first SIDE unit that you have built, remove two sets of 6 pins from the remaining BASE unit pin headers, and insert them in the pin sockets of the SIDE unit.
![](../img/c_pin_socket_6.jpg)
![](../img/3_1_trackball_l/3_1_26_pin_socket.jpg)

Place the SIDE unit on the supports and secure it with the M3 screws excessed in base unit.
> [!CAUTION]
> Make sure that the legs of the pin sockets are inside the long through-holes of the BASE unit.

![](../img/3_1_trackball_l/3_1_27_base_1.jpg)
Solder the pin sockets from the back side of the BASE unit.
![](../img/3_1_trackball_l/3_1_28_base_2.jpg)
This is the last soldering step for the SIDE unit.

In case you plan on using the OLED module, insert it in the pin socket.
![](../img/3_1_trackball_l/3_1_29_base_3.jpg)

Attach MX switches to the switch plate, and insert them in the MX sockets, and attach 3DP case.
![](../img/3_1_trackball_l/IMG_3395.jpg)

Confirm that everything is working by connecting the unit to a computer with a USB cable.
![](../img/3_1_trackball_l/IMG_3401.jpg)
> [!NOTE]
> the LEDs will not work until the TOP (and ADD) units are completed.
> trackball speed and direction can be adjusted later.

If the keys and ball are working, proceed with the TOP unit assembly
There are two types of top unit: the one included in the package, and a top unit with wheels sold separately.
4. [TOP Unit](../leftside/4_TOP.md)
   - [TOP Unit with wheel (sold separately)](../leftside/4_TOP_WHEEL.md)
