template<std::size_t _SIZE>
        std::size_t ArH::ArraySize(ArC::databuf<_SIZE> &array_obj)
        {
            return array_obj.size()-1;
        }

template<std::size_t _SIZE>
    std::size_t ArH::DataSize(ArC::databuf<_SIZE> &array_obj)
    {
        return strlen(array_obj.data());
    }

template<std::size_t _SIZE>
    void ArH::CleanData(ArC::databuf<_SIZE> &array_obj)
    {
        memset(array_obj.data(), 0, array_obj.size());
    }

template<std::size_t _SIZE>
    bool ArH::AssignData(ArC::databuf<_SIZE> &array_dest, const char source[])
    {
        if (array_dest.size() <= strlen(source))
            return false;

        if (strcpy(array_dest.data(), source) != nullptr)
            return true;
        else
            return false;
    }

template<std::size_t _SIZE>
    bool ArH::AppendData(ArC::databuf<_SIZE> &array_dest, const char source[])
    {
        if (array_dest.size() <= strlen(source) + strlen(array_dest.data()))
            return false;

        if (strcat(array_dest.data(), source) != nullptr)
            return true;
        else
            return false;
    }


