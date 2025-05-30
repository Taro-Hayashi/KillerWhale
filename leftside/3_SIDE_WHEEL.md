# Killer Whale SIDE Unit Wheel LEFT Side Build Manual （[RIGHT Side](../rightside/3_SIDE_WHEEL.md)）

1. [First Page](../README_EN.md)
2. [BASE Unit](../leftside/2_BASE.md)
3. SIDE Unit
   - [Trackball](../leftside/3_SIDE_TRACKBALL.md)
   - [D-PAD](../leftside/3_SIDE_DPAD.md)
   - Wheel (selling separately) LEFT Side
   - [Joystick (selling separately)](../leftside/3_SIDE_JOYSTICK.md)
4. [TOP Unit](../leftside/4_TOP.md)
5. [ADD Unit](../leftside/5_ADD.md)
6. [Assemble](../leftside/6_ASSEMBLE.md)
7. [Customize](../leftside/7_CUSTOM.md)
8. [Misc](../leftside/8_MISC.md)



## Contents
![](../img/3_4_wheel_l/3_1_1_contents.jpg)
Vertical and horizontal common build manuals.
||types|quantities||
|-|-|-|-|
|1|Main board|1|FR4|
|2|Switch plate|1|FR4|
|3|Cover plates|2|Acryic|
|5|M2 short screw|5|4mm|
|4|M2 middle screw|4|6mm|
|6|M2 short spacer|1|8mm|
|7|M2 middle spacers|2|9mm|
|8|M2 long spacers|2|16mm|
|9|MX hotswap sockets|2||
|10|Wheel encoder|1||
|12|Diodes|4|1N4148|
|13|Pin header|1||


The following 3D printed parts are also used.

![](../img/3_4_wheel_l/IMG_3343.jpg)


### Additional Required
|Types|quantities|
|-|-|
|Keyswitches|2|
|Keycaps|2|


### Optional Parts
<table>
    <tr>
      <td>OLED Display</a></td>
      <td>1</td>
    </tr>
    <tr>
      <td>4Pin socket</a></td>
      <td>1</td>
    </tr>
    <tr>
      <td>SK6812MINI-E</td>
      <td>3</td>
    </tr>
 </table>

## Soldering
Keep in mind that components will be placed on both sides of the unit.
![](../img/3_4_wheel_l/3_1_2_overall.jpg)
The PCB side with text in Japanese is the back side.
### Soldering of the LEDs (optional)
Solder the 3 LEDs. The round LED should be facing away from the side where soldering is done.
![](../img/3_4_wheel_l/3_1_3_led.jpg)


### Soldering of MX hotswap socket (back side)
From the back side of the unit, solder the MX hotswap sockets while keeping them in place with tweezers.

![](../img/3_4_wheel_l/3_1_4_mxsocket.jpg)

### Soldering of the diodes (back side)
Diodes are directional components. Make sure to align the lines with markings on the PCB.
![](../img/c_diode.jpg)
Insert the diodes in the 4 locations on the back side of the PCB, and solder from the front side of the PCB, and cut the diode legs.
![](../img/3_4_wheel_l/3_1_5_diodes.jpg)

### Soldering of pin headers (back side)
Cut out four sets of 6 pins from the 40 pin headers.

![](../img/c_pin_header_6.jpg)
Insert the pin headers from the back side and solder.
> [!WARNING]
> Insert the long side of the pins. In case you did it the other way around, cut the long side in order to match the length of the short side.

![](../img/3_4_wheel_l/3_1_10_pin_header.jpg)

### Soldering of OLED Display (optional, front side)
If you want to make the OLED module removable, solder a 4pin socket on the surface.
![](../img/3_4_wheel_l/3_1_11_oled_socket.jpg)

Solder the pin headers to the OLED module.
![](../img/c_oled_header.jpg)
If the OLED module is to be soldered directly, solder it to the main board at this time.
### Wheel encoder
Insert the wheel encoder from the front side and solder.
![](../img/3_4_wheel_l/3_1_12_encoder.jpg)

## Intermediate assembly and soldering of sockets

### Assembling the switch plate

If the switch plate is tagged, fold it and then sand it.
![](../img/c_switch_l.jpg)
Attach the M2 long spacers and M2 short screws to the switch plate.
> [!NOTE]
> The switch plate has an orientation (lower and top part).

![](../img/3_4_wheel_l/3_1_15_switch_1.jpg)

Attach the protection acrylic sheets to the spacers with M2 middle screws.
![](../img/3_4_wheel_l/3_1_17_switch_3.jpg)
Put the large protection acrylic sheet on top.



### Connecting to the BASE unit
Attach long M2 spacers with M2 short screws to the SIDE unit.

> [!NOTE]
> There should be one spacer on the bottom side of the SIDE unit and two to the top, forming an equilateral triangle.

![](../img/3_4_wheel_l/3_1_18_spacers.jpg)


If this is the first SIDE unit that you have built, remove two sets of 6 pins from the remaining BASE unit pin headers, and insert them in the pin sockets of the SIDE unit.
![](../img/c_pin_socket_6.jpg)
![](../img/3_4_wheel_l/3_1_19_pinsocket.jpg)

Place the SIDE unit on the supports and secure it with the M3 screws excessed in base unit.
> [!CAUTION]
> Make sure that the legs of the pin sockets are inside the long through-holes of the BASE unit.

![](../img/3_4_wheel_l/3_1_27_base_1.jpg)

Solder the pin sockets from the back side of the BASE unit.
![](../img/3_4_wheel_l/3_1_28_base_2.jpg)
This is the last soldering step for the SIDE unit.

In case you plan on using the OLED module, insert it in the pin socket.
![](../img/3_4_wheel_l/3_1_29_base_3.jpg)

Combine the wheel parts. Be careful with the direction of the axis of the thinner one.
![](../img/3_4_wheel_r/IMG_3348.jpg)
It may require a little force. The medium axis can come from either direction.
![](../img/3_4_wheel_r/IMG_3351.jpg)


Attach MX switches to the switch plate, and insert them in the MX sockets, so that the Wheel attached.
![](../img/3_4_wheel_l/3_1_30_complete.jpg)
Secure the protection plate with M2 middle  screws.


Confirm that everything is working by connecting the unit to a computer with a USB cable.
> [!NOTE]
> The LEDs will not work until the TOP (and ADD) units are completed.

If the keys are working, proceed with the TOP unit assembly
There are two types of top unit: the one included in the package, and a top unit with wheels sold separately.

4. [TOP Unit](../leftside/4_TOP.md)
   - [TOP Unit with wheel (selling separately)](../leftside/4_TOP_WHEEL.md)
