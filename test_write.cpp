#include <iostream>
#include "lib/arduino_connections.h"

using namespace std;
using namespace ArC;

int main()
{
    Arduino obj;
    buf_t _buf[]="Hello World!\n";

    cout << "\nTrying to connect with arduino ...\n";

    switch(obj.usb_pair("/dev/ttyACM0", B9600))
    {
        case 0:
            cout << "Connection succeded!\nThe connection is stored under \"" << obj.get_path() << "\"\n"
                 << "Trying to sending to Arduino ...\n";

            if(obj.send_data(_buf, sizeof _buf))
                cout << "Sending succeded!\n" << endl;
            else
                cout << "ERR: unable to send to arduino\n" << endl;

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
