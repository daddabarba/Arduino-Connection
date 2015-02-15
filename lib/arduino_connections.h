#ifndef __ARDUINO_CONNECTIONS_H__
#define __ARDUINO_CONNECTIONS_H__

#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

namespace ArC
{
    #define X_TIME 0x249F00   // 2 400 000
    #define L_TIME 0x1E8480   // 2 000 000
    #define M_TIME 0x1B7740   // 1 800 000
    #define S_TIME 0x186A00   // 1 600 000

    typedef char buf_t;

    class Arduino
    {
        private:
          // To store the file descriptor
            int _fd;
          // To store the path to the file
            char *_fpath;

            struct termios tty_table;
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
          // The Class destructor
            ~Arduino();
          // Initialize the class with proper values
            Arduino();

          // Close the connection and free memory
            void detach();

          // Start an USB connection
            int usb_pair(const char path[], const speed_t _baud, const useconds_t _init_time=L_TIME);
          /* To enstablish a proper connection to the
             device file described by the fd.
             Remember to give the same _baud you gave to arduino!
             if it cannot get the fd reuturns 0,
             if it cannot get the file flags returns -1,
             if it cannot set the new file flags returns -2,
             else, the connection succeded and returns 1. */

          // Send _nbyte data to arduino
            bool send_data(const buf_t data[], size_t _nbyte);
          /* It return true if the number of chars written
             equals the number of chars recived by the file,
             otherwise returns false */

          // Read _nbyte data from arduino
            bool get_data(buf_t data[], size_t _nbyte);
          /* It return true if the number of chars read
             equals _nbyte-1 (remember that there must be '\0' at the end of the array
             so if you want read 12 chars the size of your buf_t array must be 13),
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
