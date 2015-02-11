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

int ArC::Arduino::usb_attach(const char path[])
{
    if (this->_fpath!=nullptr)
        delete[] this->_fpath;
    if (this->_fd>=0)
        close(this->_fd);

    this->_fpath = new char[strlen(path)+1];

    strcpy(this->_fpath, path);

    this->_fd = open(path, O_RDONLY | O_NONBLOCK);

    if (_fd < 0)
        return 0;

    if (tcgetattr(_fd, &ttable) < 0)
        return -1;

    ttable.c_cflag &= ~PARENB;
    ttable.c_cflag &= ~CSTOPB;
    ttable.c_cflag &= ~CSIZE;
    ttable.c_cflag |= CS8;
    ttable.c_cflag &= ~CRTSCTS;
    ttable.c_cflag |= CREAD | CLOCAL;
    ttable.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    ttable.c_oflag &= ~OPOST;
    ttable.c_cc[VMIN]  = 0;
    ttable.c_cc[VTIME] = 0;

    cfsetospeed(&ttable, 9600);

    if (tcsetattr(_fd, TCSANOW, &ttable) < 0)
        return -2;

    return 1;
}

bool ArC::Arduino::send(const char msg[])
{
    size_t len = strlen(msg);

    if (len == write(_fd, msg, len))
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
