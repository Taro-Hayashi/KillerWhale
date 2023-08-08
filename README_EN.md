# Killer Whale Build Manual First Page（[日本語](README.md)）

1. First Page
2. [BASE Unit](rightside/2_BASE.md)
3. [SIDE Unit](rightside/3_SIDE_TRACKBALL.md)
4. [TOP Unit](rightside/4_TOP.md)
5. [ADD Unit](rightside/5_ADD.md)
6. [Assemble](rightside/6_ASSEMBLE.md)
7. [Customize](rightside/7_CUSTOM.md)
8. [Misc](rightside/8_MISC.md)

![](img/IMG_6281.jpg)     

## Additional Required
<table>
    <tr>
      <td>Keyswitches</td>
       <td>up to 30</td>
    </tr>
    <tr>
      <td>Keycaps</td> 
      <td>up to 30</td>
    </tr>
    <tr>
      <td>Raspberry Pi Pico</td>
      <td>1</td>
    </tr>
    <tr>
      <td>Micro USB cabale</td>
       <td>1</td>
    </tr>
 </table>

![](img/IMG_4615.jpg)    
### Optional Parts
<table>
    <tr>
      <td>34mm Trackball</td>
       <td>1</td>
    </tr>
    <tr>
      <td>OLED Display</td> 
      <td>1 or 2</td>
    </tr>
    <tr>
      <td>SK6812MINI-E</td>
      <td>up to 36</td>
    </tr>
    <tr>
      <td>TRRS Cable</td>
       <td>1</td>
    </tr>
 </table>

![](img/IMG_4630.jpg)    

### Optional Units
<table>
    <tr>
      <td><a href="https://tarohayashi.booth.pm/items/4877491">SIDE Unit (Vertical Wheel)</a></td> 
    </tr>
    <tr>
      <td><a href="https://tarohayashi.booth.pm/items/4877491">SIDE Unit (Horizontal Wheel)</a></td>
    </tr>
    <tr>
      <td><a href="https://tarohayashi.booth.pm/items/4877491">SIDE Unit (Joystick)</a></td>
    </tr>
    <tr>
      <td><a href="https://tarohayashi.booth.pm/items/4877486">TOP Unit with wheel</a></td>
    </tr>
 </table>

![](img/IMG_6297.jpg)     

## Preparations
### Detach the switch plates
![](img/IMG_6058.jpg)    
![](img/IMG_4649.jpg)    
![](img/IMG_4681.jpg)    

## Write firmware
Download uf2 file.
- [tarohayashi_killerwhale_solo_default.uf2
](https://github.com/Taro-Hayashi/KillerWhale/releases/download/0.21.6/tarohayashi_killerwhale_solo_default.uf2)

Connect the Raspberry Pi Pico to the PC while holding down the BOOTSEL button, it will be recognized as a USB memory device called RPI-RP2.
![](img/IMG_4689.jpg)     
![](img/rpi.jpg)     
Writing the uf2 file, it will automatically reboot.

### Decide left or right side
Decide left or right side and proceed to BASE Unit page.
- [BASE Unit LEFT Side](leftside/2_BASE.md)
- [BASE Unit RIGHT Side](rightside/2_BASE.md)

The only difference between the left and right manuals is the image.

