#Arduino Connections

This is a simple library to provide the connection between a Unix based system and the Arduino platform.
Always remember to open the arduino serial monitor and change the serial-port path,
which you can find in the Arduino IDE in "tools/serial port" in the test.cpp file 
before compiling or the connection will be impossible.

It uses the "termios.h" library, you can find information about it on this link: 
	http://man7.org/linux/man-pages/man3/termios.3.html
