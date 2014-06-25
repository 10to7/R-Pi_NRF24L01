Example of running the NRF24L01 on the R-Pi
=====

Using Occidentals:
https://learn.adafruit.com/adafruit-raspberry-pi-educational-linux-distro/occidentalis-v0-dot-2

Ensure you enable SPI.

$ git clone https://github.com/10to7/RF24.git
$ cd RF24
$ cd librf24-rpi/librf24
Compile the library
$ make                                
$ sudo make install              
$ sudo ldconfig -v | grep librf
     librf24.so.1 -> librf24.so.1.0

$ cd ../examples/
You should now be in RF24/librf24-rpi/librf24/examples

$ make

To run the programs, type 

$ sudo ./rpi-hub

To send data to the hub on a second raspberry pi run
$ sudo ./sendto_hub

Alternatively use the nRF24_sendto_hub arduino script. You will need to add the nRF24 library to your arduino ide to get the NRF24.h

Wire up your module to the arduino as follows:

|NRF24L01 	| Arduino Nano	|
|---		|---		|
|CE		| D9		|
|SS		| D10		|
|MOSI		| D11		|
|MISO		| D12		|
|SCK		| D13		|
|3v3		| 3v3		|
|GND		| GND		|

Add an additional 100uF capacitor between 3v3 and GND. The arduino nano will be able to send to the R-Pi, but it may not be able to reveive packets without the capacitor.
