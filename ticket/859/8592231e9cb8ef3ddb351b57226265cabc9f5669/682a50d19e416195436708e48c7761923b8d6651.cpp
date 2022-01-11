#include <windows.h>
#include <tchar.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING] = _T("My app title.");								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING] = _T("MyNewWindowClass");	  		// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
  // TODO: Place code here.
  MSG msg;

  // Initialize global strings
  MyRegisterClass(hInstance);

  // Perform application initialization:
  if (!InitInstance (hInstance, nCmdShow))
  {
    return FALSE;
  }

  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style			= CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc	= (WNDPROC)WndProc;
  wcex.cbClsExtra		= 0;
  wcex.cbWndExtra		= 0;
  wcex.hInstance		= hInstance;
  wcex.hIcon			= 0;
  wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName	= (LPCSTR)0;
  wcex.lpszClassName	= szWindowClass;
  wcex.hIconSm		= 0;

  return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;

  hInst = hInstance; // Store instance handle in our global variable

  hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

  if (!hWnd)
  {
    return FALSE;
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

void DrawRotatedText(RECT rc, HDC hDC,
                     int nAngleLine = 0,
                     bool bEnableAngleChar = false,
                     int nAngleChar = 0,
                     LPCTSTR lpStrFontName = _T("Courier New"),
                     int nFontSize = 12  )

{
  LOGFONT lf = { 0 };
  strcpy(lf.lfFaceName, lpStrFontName);
  lf.lfUnderline = TRUE;
  lf.lfWeight = FW_NORMAL;

  // Set the background mode to transparent for the
  // text-output operation.
  int nOldBkMode = SetBkMode(hDC, TRANSPARENT);
  // Specify the angle to draw line
  lf.lfEscapement = nAngleLine*10;
  lf.lfOrientation = lf.lfEscapement;

  int nOldGMode;
  if ( bEnableAngleChar ) // Enable character angle
  {
    // Set graphics mode to advance to enable orientation
    nOldGMode = SetGraphicsMode( hDC, GM_ADVANCED );
    // Specify the angle of characters
    lf.lfOrientation = nAngleChar*10;
  }
  else // Draw in normal mode
  {
    nOldGMode = SetGraphicsMode( hDC, GM_COMPATIBLE );
  }

  lf.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);

  // Select the new font created
  HFONT hFont = reinterpret_cast<HFONT>( CreateFontIndirect(&lf));
  HFONT hPrevFont = reinterpret_cast<HFONT>( SelectObject(hDC, hFont));

  // Draw text to screen
  const char strDraw[] = "Test string";
  TextOut(hDC, rc.right / 2, rc.bottom / 2, strDraw, strlen(strDraw));

  SelectObject(hDC, hPrevFont);
  DeleteObject(hFont);

  // Restore old values
  SetBkMode( hDC, nOldBkMode );
  SetGraphicsMode( hDC, nOldGMode );
}

void MyPaint(HWND hWnd, HDC hdc)
{
  RECT rt;
  GetClientRect(hWnd, &rt);
  DrawRotatedText(rt, hdc, -45); //Try engle -45 and -40 for example
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int wmId, wmEvent;
  PAINTSTRUCT ps;
  HDC hdc;

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    MyPaint(hWnd, hdc);
    EndPaint(hWnd, &ps);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
