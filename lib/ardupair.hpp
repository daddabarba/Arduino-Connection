
#include <termios.h>

#ifndef __ARDUPAIR_HPP__
#define __ARDUPAIR_HPP__

namespace Arduino
{
	typedef char databuf;

	const useconds_t
		LONG_DELAY   = 0x1E8480,		// 2 000 000 -> 2.0 sec
		MEDIUM_DELAY = 0x1B7740,		// 1 800 000 -> 1.8 sec
		SHORT_DELAY  = 0x186A00;		// 1 600 000 -> 1.6 sec

	class Connection
	{
	  public:
	  // The Class destructor (just close the connection)
		~Connection();
	  // Initialize the class with proper values
		Connection();

	  // Close the connection and free memory
		void detach();

	  // Start an USB connection
		int attach(const char _path[], const speed_t _baud, const useconds_t _delay = LONG_DELAY);
	  /* To enstablish a proper connection.
	   * Remember to give the same _baud you gave to arduino!
	   * OUTPUT CODES:
	   *  0 -> connection succeded
	   * -1 -> cannot get the _FileDesc
	   * -2 -> cannot get the file flags
	   * -3 -> cannot set the new file flags
	   */

	  // Send _nbyte data to arduino
		bool sendData(const databuf _data[], std::size_t _nbyte);

	  // Read _nbyte data from arduino
		bool readData(databuf _data[], std::size_t _nbyte);

	  // Return the path to the file which store the current connection
		const char* getPath();

	  // Return true while the path to the file which store the current connection exists, otherwise false.
		bool isAttached();

	  private:
		Connection(const Connection&)			= delete;
		Connection operator = (const Connection& Obj)	= delete;
		Connection operator = (Connection& Obj)		= delete;
		Connection operator = (Connection Obj)		= delete;

		int _FileDesc;		// To store the file descriptor
		char *_FilePath;	// To store the path to the file

		struct termios _TTY_Table;
	  /* This is a struct declared in the "termios.h" library
	   * containing the following flags:
	   *
	   * tcflag_t c_iflag;       input modes
	   * tcflag_t c_oflag;       output modes
	   * tcflag_t c_cflag;       control modes
	   * tcflag_t c_lflag;       local modes
	   * cc_t     c_cc[NCCS];    special characters
	   *
	   * The function "tcgetattr" will use a pointer to this structure
	   * to write on the file settings, and then, after changing them,
	   * "tcsetattr" will use this to write the new file options
	   */
	};
}

#endif
