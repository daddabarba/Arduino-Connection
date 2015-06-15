#include <unistd.h>
#include <fcntl.h>
#include <cstring>

#include "ardupair.hpp"

Arduino::Connection::~Connection()
{
    if (this->_FilePath != nullptr)
        delete[] this->_FilePath;

    if (this->_FileDesc >= 0)
        close(this->_FileDesc);
}

Arduino::Connection::Connection() : _FilePath(nullptr), _FileDesc(-1), _TTY_Table()
{}

void Arduino::Connection::detach()
{
    if (this->_FilePath != nullptr)
    {
        delete[] this->_FilePath;
        this->_FilePath = nullptr;
    }
    if (this->_FileDesc >= 0)
    {
        close(this->_FileDesc);
        this->_FileDesc = -1;
    }
}

int Arduino::Connection::attach(const char _path[], const speed_t _baud, const useconds_t _delay)
{
    if (this->_FilePath != nullptr)
        delete[] this->_FilePath;

    if (this->_FileDesc >= 0)
        close(this->_FileDesc);

    this->_FilePath = new char[strlen(_path)+1];
    strcpy(this->_FilePath, _path);

    this->_FileDesc = open(_path, O_RDWR | O_NONBLOCK | O_NDELAY | O_NOCTTY);

  // Check that the opening was right
    if (this->_FileDesc < 0)
        return -1;

  // Try to get the attributes of the file descripted by _FileDesc
    if (tcgetattr(_FileDesc, &_TTY_Table) < 0)
        return -2;

  // Set input output speeds
    cfsetispeed(&_TTY_Table, _baud);
    cfsetospeed(&_TTY_Table, _baud);

  // Special characters constants
    _TTY_Table.c_cc[VMIN]  = 1;
    _TTY_Table.c_cc[VTIME] = 0;

  // Control flags constants
    _TTY_Table.c_cflag &= ~(PARENB | PARODD | HUPCL | CSTOPB | CRTSCTS);
    _TTY_Table.c_cflag |= (CS8 | CREAD | CLOCAL);

  // Input flags constants
    _TTY_Table.c_iflag &= ~(IGNBRK | BRKINT | IGNPAR | PARMRK | INPCK | ISTRIP | INLCR | IGNCR | ICRNL | IXON |IXOFF | IUCLC | IXANY | IMAXBEL | IUTF8);

  // Output flags constants
    _TTY_Table.c_oflag &= ~(OPOST | OLCUC | OCRNL | ONOCR | ONLRET | OFILL | OFDEL);
    _TTY_Table.c_oflag |= (ONLCR | NL0 | CR0 | TAB0 | BS0 | VT0 | FF0);

  // Local flags constants
    _TTY_Table.c_lflag &= ~(ISIG | ICANON | ECHO | ECHONL | NOFLSH | XCASE | TOSTOP | ECHOPRT);
    _TTY_Table.c_lflag |= (IEXTEN | ECHOE | ECHOK | ECHOCTL | ECHOKE);

  // Flush before setting the attributes
    tcflush(_FileDesc, TCIFLUSH);

  // Set the attributes
    if (tcsetattr(_FileDesc, TCSANOW, &_TTY_Table) < 0)
        return -3;

  // To save the current attribs, #include <cstdlib> and uncomment the line below
    //system("stty -F /dev/ttyACM1 -a > attrib.txt");

  // Wait untill the changes will be initializated, code below
    usleep(_delay);

    return 0;
}

// Send _nbyte data to arduino
bool Arduino::Connection::sendData(const databuf _data[], std::size_t _nbyte)
{
    return ((write(this->_FileDesc, &_data, _nbyte) == _nbyte) ? true : false);
}

// Read _nbyte data from arduino
bool Arduino::Connection::readData(databuf _data[], std::size_t _nbyte)
{
    memset(&_data, 0, _nbyte);
    return ((read(this->_FileDesc, &_data, _nbyte) == _nbyte) ? true : false);
}

// Return the path to the file which store the current connection
const char* Arduino::Connection::getPath()
{
    return ((this->_FilePath == nullptr) ? "" : this->_FilePath);
}

// Return true while the path to the file which store the current connection exists, otherwise false.
// So it can be used also for handling unexpected disconnections.
bool Arduino::Connection::isAttached()
{
    return ((this->_FilePath == nullptr) ? false : ((access(this->_FilePath, F_OK) >= 0) ? true : false));
}
