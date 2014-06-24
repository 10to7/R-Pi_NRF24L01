Raspberry Pi NRF24L01
==================

A breakout board for one of the cheap NRF24L01 modules for Raspbery Pi.

##Module pin outs
Top view of the NRF24L01 modules pins are assumed to be:

8 Pin
```no-highlight
|GND  |3v3  |
|CE   |CSN  |
|SCK  |MOSI |
|MISO |IRQ (not connected)|
```

10 Pin
```no-highlight
|3v3  |3v3  |
|CE   |CSN  |
|SCK  |MOSI |
|MISO |IRQ (not connected)|
|GND  |GND  |
```

Please check that your modules match one of these pin layouts otherwise you risk damaging your raspberry pi or the NRF24L01 module.

| Top | Bottom |
|---|---|
|![PCBfront]|![PCBback]|

##Schematic
![Schematic]


[PCBfront]: front.png "PCB front"
[PCBback]: back.png "PCB Back"
[Schematic]: hw/r-pi_nrf24l01.png "Schematic"

Select the resistor values for the LED's. The raspberry pi can only source up to 16mA through the GPIO pins.
Suggested bill of matterials includes:

http://uk.farnell.com/ part numbers:

|Part | Description | Qty |Cost (GBP)|
|---|---|---|---|
|209-9221 | 0603 Red LED | 1 |0.054 |
|122-6372 | 0603 Green LED | 1 |0.052 |
|209-9222 | 0603 Orange LED | 1 | 0.056 |
|207-3958 | 0402 100 Ohm | 3 | 0.021 |
|175-9414 | 0805 4.7uF | 1 | 0.041 |

2.54mm female headers are also required for the board. A single 2x13 16 position header for the raspberry pi and a 2x4 8 position or 2x5 10 position female header for the NRF24L01 module.
