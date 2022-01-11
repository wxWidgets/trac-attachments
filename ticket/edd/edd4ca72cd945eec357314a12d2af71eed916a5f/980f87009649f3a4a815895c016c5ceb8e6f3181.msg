Subject:      Re: Re[2]: openGL samples crashing
From:         Simone Lazzaris <simone.lazzaris@dropmetask84.it>
Newsgroups:   comp.soft-sys.wxwindows
Date:         6 Feb 2006 09:24:13 +0100

On Sun, 05 Feb 2006 22:59:59 +0100, Vadim Zeitlin wrote:

> 
>  Maybe I should have been more precise: by backtrace I meant the output
> from your debugger when it crashes.
> 

I've debugged the cube.exe sample with the turbo debugger.
The problem seems to be, indeed, a stack overflow;
here is the stack trace the turbo debugger gives to me:


xListKey::wxListKey(long)(1376872)
xHashTableBase::GetNode(1376872, 1376872)
wxWinHashTable::Get(1376872, 1376872)
wxWinHashTable::Get(1376872)
wxFindWinFromHandle(:00150268)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5
wxWindow::MSWDefWindowProc(135, 0, 0)
wxWindow::MSWWindowProc(135, 0, 0)
wxWndProc(:00150268, 135, 0, 0)
:77E72C6A
:77E72CF5

77e72cf5 seems to be inside of USER32.dll:DefWindowProcA;
77e72c6a seems to be inside USER32.dll:GetFocus.

Obviously, the problem is not located in a recursive function;
I think it has something to be something related to the event
handling: a message loop is innescated, so the window that 
get the focus send some message which re-triggers the 
event handling procedure again and again;
the event is the number 135 (0x0087) which seems to be
WM_GETDLGCODE.

I don't know whats happens in the non-dll case, and I don't 
know what to do to correct the issue, but I can make all the
testing needed to solve it.

Thanks in advance.
Simone Lazzaris

 	  	 
