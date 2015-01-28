size_t apt::GetSize(const char _str[])
{
    if (_str!=NULL)
    {
        size_t i;
        
        for (i=0; _str[i]!='\0'; i++)
        {}
        
        return i; // return the number of chars in the string, '\0' escluded.
    }
    else
        return 0;
}

apt::Arduino::~Arduino()
{
    close(fd);
}

apt::Arduino::Arduino(const char path[])
{
     fd = open(path, O_RDWR | O_NONBLOCK );
}

int apt::Arduino::Connect()
{
    if(fd<0)
        return -1;
    
    if(tcgetattr(fd,&ttable)<0)
        return -2;
    
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
    
    cfsetospeed(&ttable,9600);
    
    if(tcsetattr(fd,TCSANOW,&ttable)<0)
        return -3;
    else
        return 0;
}

bool apt::Arduino::Write(const char str[])
{
    size_t len = apt::GetSize(str);
    
    if(len == write(fd,str,len))
        return true;
    else
        return false;
}




