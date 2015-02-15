#ifndef __ARDUINO_HELPER_H__
#define __ARDUINO_HELPER_H__

    #ifndef __ARDUINO_CONNECTIONS_H__
        #error "Missing: arduino_connections.h. You must include it before using this helper library"
    #endif

namespace ArH
{
  // Return the size of the array excluding the last position that must always have '\0'
    template<std::size_t _SIZE>
        std::size_t ArraySize(ArC::databuf<_SIZE> &array_obj);

  // Return the size of stored data into the array
    template<std::size_t _SIZE>
        std::size_t DataSize(ArC::databuf<_SIZE> &array_obj);

  // Clean the data stored in the array
    template<std::size_t _SIZE>
        void CleanData(ArC::databuf<_SIZE> &array_obj);

  // Save a string in the array
    template<std::size_t _SIZE>
        bool AssignData(ArC::databuf<_SIZE> &array_dest, const char source[]);

  // Append a string after the stored data in the array
    template<std::size_t _SIZE>
        bool AppendData(ArC::databuf<_SIZE> &array_dest, const char source[]);
}

#include "arduino_helper.cpp"

#endif // __ARDUINO_HELPER_H__
