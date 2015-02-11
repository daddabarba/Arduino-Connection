#include <iostream>
#include "lib/arduino_connections.h"

using namespace std;
using namespace ArC;

int main()
{
    Arduino obj;

    cout << "\nTrying to connect with arduino ...\n";

    switch(obj.usb_attach("/dev/tty.usbmodem3a21"))
    {
        case 1:
            cout << "Connection succeded!\nThe connection is stored in \"" << obj.get_path() << "\"\n";

            if(obj.send_data("Hello World!\n"))
                cout << "Sending succeded!\n" << endl;
            else
                cout << "ERR: unable to send to arduino\n" << endl;

            break;

        case 0:
            cout << "ERR: cannot get the file descriptor\n" << endl;
            break;

        case -1:
            cout << "ERR: could not get terminal options\n" << endl;
            break;

        case -2:
            cout << "ERR: could not set new terminal options\n" << endl;
            break;

        default:
            cout << "ERR: something went wrong while connecting\n" << endl;
            break;
    }

    return 0;
}
