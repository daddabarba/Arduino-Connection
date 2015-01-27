#include <iostream>
#include "arduino_port/arduino_port.h"

using namespace std;
using namespace apt;

int main()
{

    char stringa[40];
    
   Arduino obj("/dev/tty.usbmodem3a21");
    
    cout<<"object created"<<endl<<"checking connection..."<<endl;
    
    switch(obj.Connect())
    {
        case -1:
            cout<<"ERR: cannot get the file descriptor"<<endl;
            return 0;
            break;
        
        case -2:
            cout<<"ERR: could not get terminal options"<<endl;
            return 0;
            break;
        
        case -3:
            cout<<"ERR: could not set new terminal options"<<endl;
            return 0;
            break;
            
        case 0:
            cout<<"Connection succeded!!"<<endl;
            break;
            
        default:
            break;
    }
    
    cin>>stringa;
    
    if(obj.Writes(stringa)==true)
    {
        cout<<"Sending succeded!!!"<<endl;
    }
    else
    {
        cout<<"ERR: could not send to arduino"<<endl;
    }
    
    
    return 0;
}
