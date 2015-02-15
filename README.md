#Arduino Connections

This is a simple library to provide the connection between a Unix based system and the Arduino platform.
Always remember to open the arduino serial monitor and change the serial-port path,
which you can find in the Arduino IDE in "tools/serial port" in the test.cpp file 
before compiling or the connection will be impossible.

It requires the c++ 11 standard and below there is a list of some libraries that it included:

"termios.h": http://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html and http://linux.die.net/man/3/termios 
"unistd.h":  http://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html
