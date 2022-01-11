/* A demonstration of a wxWindows bug by Dennis Taylor (dennis@funkplanet.com).
 * The wxSocketClient::IsConnected() method returns true regardless of whether
 * the connection was successfully established or not.
 *
 * Output on my x86 Debian Linux box, wxGTK 2.3.2:
 *
 * [dennis@bluesky tmp]$ ./test 
 * Connecting to bluesky... (15 seconds)
 * NOT REALLY CONNECTED!
 * [dennis@bluesky tmp]$ echo $?
 * 255
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <wx/wx.h>
#include <wx/config.h>
#include <wx/socket.h>

class TestApp : public wxApp {
 public:
  bool OnInit() {
    int timeout = 15;

    wxIPV4address addr;
    addr.LocalHost();
    addr.Service( 44444 );    // unused port, verified with lsof

    wxSocketClient sock;
    sock.Connect( addr, FALSE );

    wxBeginBusyCursor();
    do {
      printf( "Connecting to %s... (%d second%s)\n", addr.Hostname().c_str(),
	      timeout, timeout == 1 ? "" : "s" );
      timeout--;
    } while (sock.WaitOnConnect( 1 ) == FALSE && timeout > 0);
    wxEndBusyCursor();

    if (sock.IsConnected()) {
      fprintf( stderr, "NOT REALLY CONNECTED!\n" );
      return false;

    } else {
      printf( "Couldn't connect to %s: %s", addr.Hostname().c_str(),
		    wxSysErrorMsg() );
    }
    return true;
  }

  int OnExit() {
    puts( "OnExit called." );
    return EXIT_SUCCESS;
  }
};

IMPLEMENT_APP( TestApp );


 	  	 
