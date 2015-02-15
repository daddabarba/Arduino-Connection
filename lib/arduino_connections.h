#ifndef __ARDUINO_CONNECTIONS_H__
#define __ARDUINO_CONNECTIONS_H__

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <array>

namespace ArC
{
    typedef char buf_t;

    template<std::size_t _ASIZE>
        using databuf = std::array<buf_t, _ASIZE>;

    const useconds_t
        X_TIME = 0x249F00,   // 2 400 000 -> 2.4 sec
        L_TIME = 0x1E8480,   // 2 000 000 -> 2.0 sec
        M_TIME = 0x1B7740,   // 1 800 000 -> 1.8 sec
        S_TIME = 0x186A00;   // 1 600 000 -> 1.6 sec

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
             if it cannot get the fd reuturns -1,
             if it cannot get the file flags returns -2,
             if it cannot set the new file flags returns -3,
             else, the connection succeded and returns 0. */

          // Send data to arduino
          template<std::size_t _SIZE>
            bool send_data(const databuf<_SIZE>  &_data);
          /* It will send all the data stored in _data
             It return true if the number of chars written
             equals the number of chars recived by the file,
             otherwise returns false */

          // Read data from arduino
          template<std::size_t _SIZE>
            bool get_data(databuf<_SIZE> &_data);
          /* It will read until _data is filled
             It return true if the number of chars written
             is equals to the size of _data-1 (the last element in the array must be '\0'),
             otherwise returns false */

          // Send (formatted) _nbyte data to arduino
          template<std::size_t _SIZE>
            bool send_f_data(const databuf<_SIZE> &_data, std::size_t _nbyte);
          /* It will send the first _nbyte data stored in _data
             It return true if the number of chars written
             equals the number of chars recived by the file,
             otherwise returns false */

          // Read (formatted) _nbyte data from arduino
          template<std::size_t _SIZE>
            bool get_f_data(databuf<_SIZE> &_data, std::size_t _nbyte);
          /* It will read only _nbyte data and save them in _data
             It return true if the number of chars read equals _nbyte
             (_nbyte can NOT be equal or greater than the size of the array because the last element in the array must be '\0')
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
