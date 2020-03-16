![](images/MicrochipLogo.png)

# PIC18F47Q10 Using TMR1 to trigger a special event

## Objective:
This example shows how to use the TMR1 configured as a counter. The Capture/Compare/PWM (CCP) module will be configured with a user defined value. A GPIO pin will be configured as output and the event will toggle the logic value of this pin. The event will be triggered when the counted value from TMR1 will be equal with the CCP value.


## Resources:
- Technical Brief Link [(linkTBD)](http://www.microchip.com/)
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- PIC18F47Q10 Curiosity Nano [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)
- [PIC18F47Q10 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40002043D.pdf) for more information or specifications.

## Hardware Configuration:

The PIC18F47Q10 Curiosity Nano Development Board [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029) is used as a test platform.

![](images/PIC18F47Q10-Curiosity-Nano.png)

## Demo:
Run the code. Pin RB0 is configured as digital output. The logic value of the pin will toggle every time the event occurs.
