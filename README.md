# amiga_jojstick
Converter for Amiga jojstick (emulate mumpad) based on Arduino Leonardo or Micro with MEGA32U4
# HID keyboard
- https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
- https://www.usb.org/hid
# Used technology 
- Arduino IDE (https://www.arduino.cc/en/Main/Software)
- Arduino Leonardo (https://www.arduino.cc/en/Main/Arduino_BoardLeonardo) or Micro (https://store.arduino.cc/arduino-micro)
- Microchip MEGA32U4 (http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf)
- Amiga jojstick connector (https://en.wikipedia.org/wiki/D-subminiature)
# Used library
- No external library requiered
# Connection
<table>
<tr>
 <th scope="col">Signal</th>
 <th scope="col">Arduino GPIO</th>
 <th scope="col">Amiga port</th>
</tr>
<tr>
 <td>Up</td>
 <td>2</td>
 <td>1</td>
</tr>
<tr>
 <td>Down</td>
 <td>3</td>
 <td>2</td>
</tr>
<tr>
 <td>Left</td>
 <td>4</td>
 <td>3</td>
</tr>
<tr>
 <td>Right</td>
 <td>5</td>
 <td>4</td>
</tr>
<tr>
 <td>Fire</td>
 <td>6</td>
 <td>6</td>
</tr>
<tr>
 <td>Ground</td>
 <td>Gnd</td>
 <td>8</td>
</tr>
<tr>
 <td>Power</td>
 <td>+5V</td>
 <td>7</td>
</tr>
</table>
