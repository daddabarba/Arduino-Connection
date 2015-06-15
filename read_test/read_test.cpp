#include <iostream>
#include "../lib/ardupair.hpp"

using namespace std;
using namespace Arduino;

int main()
{
    Connection obj;

    databuf buffer[15] = {};

    cout << "\nTrying to connect with arduino ...\n";

  // Remember to change B9600 with your baud rate
    switch(obj.attach("/dev/tty.usbmodem3a21", B9600))
    {
        case 0:
            cout << "Connection succeded!\nThe connection is stored under \"" << obj.getPath() << "\"\n"
                 << "Trying to reading from Arduino ...\n";

            if (obj.readData(buffer, sizeof(buffer)-1))
                cout << "Reading ...\nArduino said: \"" << buffer << "\"" << endl;
            else
                cout << "Unable to read correctly from Arduino\nGotten data: \"" << buffer << "\"" << endl;

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
