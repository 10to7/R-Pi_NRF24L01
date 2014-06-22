Raspberry Pi NRF24L01
==================

A breakout board for one of the cheap NRF24L01 modules for Raspbery Pi.

##Module pin outs
Top view of the NRF20L01 modules pins are assumed to be:

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

Please check that your modules match one of these pin layouts otherwise you risk damaging your raspberry pi or the NRF20L01 module.

| Top | Bottom |
|---|---|
|![PCBfront]|![PCBback]|

##Schematic
![Schematic]


[PCBfront]: front.png "PCB front"
[PCBback]: back.png "PCB Back"
[Schematic]: hw/r-pi_nrf24l01.png "Schematic"

