#ifndef __ARDUINO_PORT_H__
#define __ARDUINO_PORT_H__

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <string>

using namespace std;

namespace apt
{
    size_t Get_size(const char str[]);
    
    class Arduino
    {
        private:
        
            int fd;
            struct termios ttable;
            /* a struct declared in the "termios.h" library
            containing the following flags:
             
            tcflag_t c_iflag;       input modes
            tcflag_t c_oflag;       output modes
            tcflag_t c_cflag;       control modes
            tcflag_t c_lflag;       local modes
            cc_t     c_cc[NCCS];    special characters 
             
            the function "tcgetattr" will use a pointer to this structure
            to write on It the file settings, and then, after changing them,
            "tcsetattr" will use this to write the new file options*/

        
        public:
        
            ~Arduino(); // the Class destructor
            Arduino(const char path[]);//the Class initializer
        
            int Connect();
            /* to connect properly the file described by the fd
            from the path given , to arduino.
            if It cannot get the fd reuturns -1,
            if It cannot get the file flags returns -2,
            if It cannot set the new file flags returns -3,
            else, if It connects successfully returns 0. */
        
            bool Writes(const char str[]);
            /* It return true if the number of chars written
            equals the number of chars recived by the file,
            otherwise returns false */
        
        
    };
    
}

    #include "arduino_port.cpp"

#endif
