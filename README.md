# sk6812 RGBW 

C code with inline assembly to control the color of *n* sk6812 RGBW LEDs.

Developed and tested with
* [AVR Dragon Programmer](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/ATAVRDRAGON)
* [atmega324pa microcontroller](https://www.microchip.com/wwwproducts/en/ATmega328p)
* [sk6812 LED](https://www.adafruit.com/product/1655)

Update variables in [Makefile](./Makefile) to use another programmer/AVR device

## Device Connection
```
sudo make connect # check connection with device (default: m324p)
sudo make erase # (optional)
```

## Compile flash AVR
```
make compile # create hex file
sudo make flash # flash the hex file to device (default: m324p)
```
