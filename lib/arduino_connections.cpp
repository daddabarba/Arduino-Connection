ArC::Arduino::~Arduino()
{
    if (this->_fpath!=nullptr)
        delete[] this->_fpath;
    if (this->_fd>=0)
        close(this->_fd);
}

ArC::Arduino::Arduino()
{
    this->_fpath = nullptr;
    this->_fd = -1;
}

void ArC::Arduino::detach()
{
    if (this->_fpath!=nullptr)
    {
        delete[] this->_fpath;
        this->_fpath=nullptr;
    }
    if (this->_fd>=0)
    {
        close(this->_fd);
        this->_fd=-1;
    }
}

int ArC::Arduino::usb_pair(const char path[], const speed_t _baud, const useconds_t _init_time)
{
    if (this->_fpath!=nullptr)
        delete[] this->_fpath;
    if (this->_fd>=0)
        close(this->_fd);

    this->_fpath = new char[strlen(path)+1];

    strcpy(this->_fpath, path);

    this->_fd = open(path, O_RDWR | O_NONBLOCK | O_NDELAY | O_NOCTTY);

  // Check that the opening was right
    if (this->_fd < 0)
        return -1;

  // Try to get the attributes of the file descripted by _fd
    if (tcgetattr(_fd, &tty_table) < 0)
        return -2;

  // Set input output speeds
    cfsetispeed(&tty_table, _baud);
    cfsetospeed(&tty_table, _baud);

  // Special characters constants
    tty_table.c_cc[VMIN]  = 1;
    tty_table.c_cc[VTIME] = 0;

  // Control flags constants
    tty_table.c_cflag &= ~(PARENB | PARODD | HUPCL | CSTOPB | CRTSCTS);
    tty_table.c_cflag |= (CS8 | CREAD | CLOCAL);

  // Input flags constants
    tty_table.c_iflag &= ~(IGNBRK | BRKINT | IGNPAR | PARMRK | INPCK | ISTRIP | INLCR | IGNCR | ICRNL | IXON |IXOFF | IUCLC | IXANY | IMAXBEL | IUTF8);

  // Output flags constants
    tty_table.c_oflag &= ~(OPOST | OLCUC | OCRNL | ONOCR | ONLRET | OFILL | OFDEL);
    tty_table.c_oflag |= (ONLCR | NL0 | CR0 | TAB0 | BS0 | VT0 | FF0);

  // Local flags constants
    tty_table.c_lflag &= ~(ISIG | ICANON | ECHO | ECHONL | NOFLSH | XCASE | TOSTOP | ECHOPRT);
    tty_table.c_lflag |= (IEXTEN | ECHOE | ECHOK | ECHOCTL | ECHOKE);

  // Flush before setting the attributes
    tcflush(_fd, TCIFLUSH);

  // Set the attributes
    if (tcsetattr(_fd, TCSANOW, &tty_table) < 0)
        return -3;

  // To save the current attribs, #include <cstdlib> and uncomment the line below
    //system("stty -F /dev/ttyACM1 -a > attrib.txt");

  // Wait untill the changes will be initializated, code below
    usleep(_init_time);

    return 0;
}

template<std::size_t SIZE>
    bool ArC::Arduino::send_data(const std::array<ArC::buf_t, SIZE>& _data)
    {
        if (write(_fd, _data.data(), _data.size()) == _data.size())
            return true;
        else
            return false;
    }

template<std::size_t SIZE>
    bool ArC::Arduino::get_data(std::array<ArC::buf_t, SIZE>& _data)
    {
        std::size_t _nbyte = _data.size()-1;

        memset(_data.data(), 0, _nbyte+1);

        if (read(_fd, _data.data(), _nbyte) == _nbyte)
            return true;
        else
            return false;
    }

template<std::size_t SIZE>
    bool ArC::Arduino::send_f_data(const std::array<ArC::buf_t, SIZE>& _data, std::size_t _nbyte)
    {
        if (write(_fd, _data.data(), _nbyte) == _nbyte)
            return true;
        else
            return false;
    }

template<std::size_t SIZE>
    bool ArC::Arduino::get_f_data(std::array<ArC::buf_t, SIZE>& _data, std::size_t _nbyte)
    {
        memset(_data.data(), 0, _data.size());

        if (_nbyte >= _data.size())
            return false;

        if (read(_fd, _data.data(), _nbyte) == _nbyte)
            return true;
        else
            return false;
    }

inline const char* ArC::Arduino::get_path()
{
    return (this->_fpath == nullptr ? "" : this->_fpath);
}

inline bool ArC::Arduino::is_attached()
{
    if (this->_fpath!=nullptr)
        return (access(this->_fpath, F_OK) >= 0 ? true : false);
    else
        return false;
}
