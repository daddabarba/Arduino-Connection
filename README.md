#Arduino Pair

This is a simple library to provide the connection between a Unix based system and the Arduino platform.<br><br>
Always remember to open the arduino serial monitor and change the serial-port path,<br>
(which you can find in the Arduino IDE under "tools/serial port") in the test files 
before compiling or the connection will be impossible.

It requires the c++ 11 standard, below there are some links to libraries that are used.

"termios.h":<br>
http://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html<br>
http://linux.die.net/man/3/termios<br>

"unistd.h":<br>
http://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html
