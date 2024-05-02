# Killer Whale BASE Unit RIGHT Side Build Manual （[LEFT Side](../leftside/2_BASE.md)）

1. [Start Page](../README_EN.md)
2. BASE Unit RIGHT Side
3. [SIDE Unit](../rightside/3_SIDE_TRACKBALL.md)
4. [TOP Unit](../rightside/4_TOP.md)
5. [ADDITIONAL Unit](../rightside/5_ADD.md)
6. [Assembly](../rightside/6_ASSEMBLE.md)
7. [Customizations](../rightside/7_CUSTOM.md)
8. [Misc](../rightside/8_MISC.md)

## Contents
![](../img/2_base_r/2_1_contents.jpg)      
||Types|Quantities||
|-|-|-|-|
|1|Main Board|1|FR4|
|2|Bottom Plate|1|Acrylic|
|3|SIDE Unit Pillar|4|Acrylic|
|4|TOP Unit Pillar|4|Acrylic|
|5|M2 silver screw|12|10mm|
|6|M2 silver washers|24||
|7|M2 silver spring washers|12||
|8|M2 silver nuts|12||
|9|M2 spacers|12|3mm|
|10|M3 screws|11|10mm|
|11|M3 square nuts|11||
|12|M2 black screws|4|8mm|
|13|M2 black washers|8||
|14|M2 black spring washers|4|
|15|M2 black nuts|4|
|16|TRRS jacks|2||
|17|Pin sockets|2||
|18|Angle pin socket|1||
|19|Pin headers|2||
|20|Jumpers|6||
|21|Rubber feet|4||
|22|MOSFET|4|BSS138|
|23|Resistors|4|10k|

 
## Soldering
The components of the BASE unit are all placed on the front side.
![](../img/2_base_r/2_2_overall.jpg)   

### Soldering of the Raspberry Pi Pico
Separate the pin header into sets of 20 pins with a nipper. 
![](../img/2_base_r/2_3_pin_header.jpg)    
Insert the pins in the holes in the PCB, place the Raspberry Pi Pico.
![](../img/2_base_r/2_4_raspberry_pi_pico_1.jpg)   
> [!WARNING]  
> Be careful to place the Raspberry Pi Pico on the correct side - you can confirm this by checking the position of GP0 and VBUS. Once this is done, proceed with soldering.

![](../img/2_base_r/2_5_raspberry_pi_pico_2.jpg)      
Solder from the front and back side. Cut the long side of the pins with a nipper.
![](../img/2_base_r/2_6_raspberry_pi_pico_3.jpg)    

### Soldering of Angle Pin Socket
Place the socket, then solder from the back side.
![](../img/2_base_r/2_7_angle_sockert.jpg)       

### Soldering of TRRS Jacks
Place the trrs jacks, then solder from the back side.
![ ](../img/2_base_r/2_8_trrs.jpg)      

### Jumpers
From the pin headers, cut out two sets of 3 pins, and 8 sets of 4 pins.

![](../img/2_base_r/2_9_pin_header_1.jpg)   

Solder them in the area delimitated by frames. Insert the short side in holes so that the long side is stick out from the front side of the PCB.

![](../img/2_base_r/2_10_pin_header_2.jpg)    
Insert 6 jumpers at 3 locations according to your planned configuration.

![](../img/2_base_r/2_11_jumper.jpg)      
For the LEFT BASE unit, in case you plan to have the ADD unit and a keypad based SIDE unit, the jumper placement should be the same as the picture below.


### Soldering of the LEDs (optional)
Since the components are very small, manipulate them with tweezers during soldering in order to avoid getting burned.
![](../img/2_base_r/2_12_mosfet.jpg)          

LEDs have a direction. Make sure that the round part emitting light is facing away by placing the cut leg of LEDs on the pad with a mark on the PCB.
![](../img/c_led.jpg)       
There are 3 locations for LEDs on the base unit.

![](../img/2_base_r/2_13_sk6812mini_e.jpg) 
Connect a USB cable and check if the LEDs are working.

## Supports
### Assembly of the supports
4 supports must be prepared with the 8 acrylic sheets.
![](../img/2_base_r/2_14_pillars.jpg)    
Thread the M2 silver washers onto 12 M2 silver screws.

![](../img/2_base_r/2_15_m2screw.jpg)    

Insert the M2 screws with washers into one side of the pillars, and secure with M2 spacers.
![](../img/2_base_r/2_16_pillar_1.jpg)    
Insert the square nut diagonally into the slits of the supports. The small support has 2 slits, the medium on 3 and the large one 4. 
![](../img/2_base_r/2_17_pillar_2.jpg)    
Place the other side of the support and insert washers and spring washers, and secure with a nut.
![](../img/2_base_r/2_18_pillar_3.jpg)     


At this point, the 4 supports are complete.
![](../img/2_base_r/2_19_pillars_complete.jpg)   

### Assembly of the support onto the unit
Place the pillar on the front side of the PCB and secure them from the back side with M3 screws. 
![](../img/2_base_r/2_20_base_complete.jpg)    
> [!NOTE]
> As they will be removed later, do not tighten them too much.

Remaining parts will be used in later steps, therefore keep them at hand. 

Now you can proceed to the build guide of the SIDE unit that you are planning to use.

3. SIDE Unit
   - [Trackball](../rightside/3_SIDE_TRACKBALL.md)
   - [D-PAD](../rightside/3_SIDE_DPAD.md)
   - [Wheel (sold separately)](../rightside/3_SIDE_WHEEL.md)
   - [Joystick (sold separately)](../rightside/3_SIDE_JOYSTICK.md)
