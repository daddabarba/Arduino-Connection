#include <iostream>
#include "arduino_port/arduino_port.h"

using namespace std;
using namespace apt;

int main()
{
    char str[40];

    Arduino obj("/dev/ttyACM0");

    cout << "\nObject created!\nChecking connection ...\n";

    switch(obj.SafeConnect())
    {
        case -1:
            cout << "ERR: cannot get the file descriptor\n" << endl;
            return 0;
        break;

        case -2:
            cout << "ERR: could not get terminal options\n" << endl;
            return 0;
        break;

        case -3:
            cout << "ERR: could not set new terminal options\n" << endl;
            return 0;
        break;

        case 0:
            cout << "Connection succeded!\n\n";
        break;

        default:
        break;
    }

    cout << "Enter text to send: ";
    cin >> str;

    if(obj.Write(str))
        cout << "\nSending succeded!\n" << endl;
    else
        cout << "\nERR: could not send to arduino\nClosing the program ... \n" << endl;

    return 0;
}
