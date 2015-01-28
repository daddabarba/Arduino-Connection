#include <iostream>
#include "arduino_port/arduino_port.h"

using namespace std;
using namespace apt;

int main()
{

    char stringa[40];
    
    Arduino obj("/dev/tty.usbmodem3a21");
    
    cout<<"object created"<<endl<<"checking connection...\n"<<endl;
    
    switch(obj.Connect())
    {
        case -1:
            cout<<"ERR: cannot get the file descriptor\n"<<endl;
            return 0;
            break;
        
        case -2:
            cout<<"ERR: could not get terminal options\n"<<endl;
            return 0;
            break;
        
        case -3:
            cout<<"ERR: could not set new terminal options\n"<<endl;
            return 0;
            break;
            
        case 0:
            cout<<"Connection succeded!\n"<<endl;
            break;
            
        default:
            break;
    }
    
    cin>>stringa;
    
    if(obj.Write(stringa)==true)
    {
        cout<<"Sending succeded!\n"<<endl;
    }
    else
    {
        cout<<"ERR: could not send to arduino\n"<<endl;
    }
    
    
    return 0;
}
