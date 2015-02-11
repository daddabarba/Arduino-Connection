#ifndef __ARDUINO_CONNECTIONS_H__
#define __ARDUINO_CONNECTIONS_H__

#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

namespace ArC
{
    class Arduino
    {
        private:
          // To store the file descriptor
            int _fd;
          // To store the path to the file
            char *_fpath;

            struct termios ttable;
          /* This is a struct declared in the "termios.h" library
             containing the following flags:

             tcflag_t c_iflag;       input modes
             tcflag_t c_oflag;       output modes
             tcflag_t c_cflag;       control modes
             tcflag_t c_lflag;       local modes
             cc_t     c_cc[NCCS];    special characters

             The function "tcgetattr" will use a pointer to this structure
             to write on the file settings, and then, after changing them,
             "tcsetattr" will use this to write the new file options */

        public:
          // the Class destructor
            ~Arduino();
          // Initialize the class with proper values
            Arduino();

          // Close the connection and free memory
            void detach();

          // Start an USB connection
            int usb_attach(const char path[]);
          /* To enstablish a proper connection to the
             device file described by the fd.
             if it cannot get the fd reuturns 0,
             if it cannot get the file flags returns -1,
             if it cannot set the new file flags returns -2,
             else, the connection succeded and returns 1. */

          // send your data to arduino
            bool send_data(const char msg[]);
          /* It return true if the number of chars written
             equals the number of chars recived by the file,
             otherwise returns false */

          // Return the path to the file which store the current connection
            inline const char* get_path();

          // Return true while the path to the file which store the current connection exists, otherwise false.
          // So it can be used also for handling unexpected disconnections.
            inline bool is_attached();

    };
}

#include "arduino_connections.cpp"

#endif
