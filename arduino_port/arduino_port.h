#ifndef __ARDUINO_PORT_H__
#define __ARDUINO_PORT_H__

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

namespace apt
{
    size_t GetSize(const char str[]);
    
    class Arduino
    {
        private:
        
            int fd;
            struct termios ttable;
            /* This is a struct declared in the "termios.h" library
            containing the following flags:
             
            tcflag_t c_iflag;       input modes
            tcflag_t c_oflag;       output modes
            tcflag_t c_cflag;       control modes
            tcflag_t c_lflag;       local modes
            cc_t     c_cc[NCCS];    special characters 
             
            The function "tcgetattr" will use a pointer to this structure
            to write on It the file settings, and then, after changing them,
            "tcsetattr" will use this to write the new file options*/

        
        public:
        
            ~Arduino(); // the Class destructor
            Arduino(const char path[]);//the Class initializer
        
            int Connect();
            /* To enstablish a proper connection to the
            device file described by the fd.
            if it cannot get the fd reuturns -1,
            if it cannot get the file flags returns -2,
            if it cannot set the new file flags returns -3,
            else, the connection succeded and returns 0. */
        
            bool Write(const char str[]);
            /* It return true if the number of chars written
            equals the number of chars recived by the file,
            otherwise returns false */
        
        
    };
    
}

#include "arduino_port.cpp"

#endif
