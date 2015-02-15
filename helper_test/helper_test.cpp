#include "../lib/arduino_connections.h"
#include "../lib/arduino_helper.h"

#include <iostream>

using namespace std;

int main()
{
    ArC::databuf<12> buf = {"Hello World"};

    cout << "\nData Size: " << ArH::DataSize(buf)
         << "\nArray Size: " << ArH::ArraySize(buf) << "\n"
         << "Data: " << buf.data() << "\n\n";

    ArH::AssignData(buf, "Hello");

    cout << "Data Size: " << ArH::DataSize(buf)
         << "\nArray Size: " << ArH::ArraySize(buf) << "\n"
         << "Data: " << buf.data() << "\n\n";

    ArH::AppendData(buf, " again");

    cout << "Data Size: " << ArH::DataSize(buf)
         << "\nArray Size: " << ArH::ArraySize(buf) << "\n"
         << "Data: " << buf.data() << "\n\n";

    ArH::CleanData(buf);

    cout << "Data Size: " << ArH::DataSize(buf)
         << "\nArray Size: " << ArH::ArraySize(buf) << "\n"
         << "Data: " << buf.data() << "\n\n";

    return 0;
}
