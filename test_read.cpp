#include <iostream>
#include "lib/arduino_connections.h"

using namespace std;
using namespace ArC;

int main()
{
    Arduino obj;

  // Same as std::array<buf_t, 7> _buf = {0};
    databuf<7> _buf = {0};

    cout << "\nTrying to connect with arduino ...\n";

  // Remember to change B9600 with your baud rate
    switch(obj.usb_pair("/dev/ttyACM0", B9600))
    {
        case 0:
            cout << "Connection succeded!\nThe connection is stored under \"" << obj.get_path() << "\"\n"
                 << "Trying to reading from Arduino ...\n";

            if (obj.get_data(_buf))
                cout << "Reading 1, Arduino said: \"" << _buf.data() << "\"" << endl;
            else
                cout << "Unable to read correctly from Arduino\nGotten data: \"" << _buf.data() << "\"" << endl;

            if (obj.get_f_data(_buf, 6))
                cout << "Reading 2, Arduino said: \"" << _buf.data() << "\"" << endl;
            else
                cout << "Unable to read correctly from Arduino\nGotten data: \"" << _buf.data() << "\"" << endl;

            break;

        case -1:
            cout << "ERR: cannot get the file descriptor\n" << endl;
            break;

        case -2:
            cout << "ERR: could not get terminal options\n" << endl;
            break;

        case -3:
            cout << "ERR: could not set new terminal options\n" << endl;
            break;

        default:
            cout << "ERR: something went wrong while connecting\n" << endl;
            break;
    }

    return 0;
}
