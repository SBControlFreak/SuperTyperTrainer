// SuperTyperTrainer.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SuperTyperTrainer.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SUPERTYPERTRAINER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SUPERTYPERTRAINER));

    MSG msg;

    // Main message loop:
    while (true)
    {
        steady_clock::time_point t1 = steady_clock::now();
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }
        steady_clock::time_point t2 = steady_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    }
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUPERTYPERTRAINER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SUPERTYPERTRAINER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, SW_MAXIMIZE);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WPARAM tempTest = 'e';
    HMENU Hmenu = GetMenu(hWnd);
   
    switch (message)
    {
    case WM_CREATE:
        {
            MainGraph.GraphicObject.CreateG_Resources(hWnd);

            LocTest_.left = 50;
            LocTest_.right = 100;
            LocTest_.top = 100;
            LocTest_.bottom = 150;
        }
        //Disable Start - Profiles need to be set up first
        EnableMenuItem(Hmenu, 110, MF_GRAYED);
        //Disable Stop - Game is not running
        EnableMenuItem(Hmenu, 111, MF_GRAYED);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_START:
                //MainGraph.WinMessageBox(L"Start", L"Message", MB_OK);
                MessageBox(hWnd, L"Start", L"Message", MB_OK);
                break;
            case IDM_PAUSE:
                MessageBox(hWnd, L"Pause", L"Message", MB_OK);
                break;
            case IDM_SETTINGS:
                MessageBox(hWnd, L"Settings", L"Message", MB_OK);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            MainGraph.BeginDraw();

            KeyBoardCon.DrawUpdate(5.76, false);
            
            MainGraph.EndDraw();

            //TODO: Needed for message box to work....but why?
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:
        {
            MainGraph.Resize();
            KeyBoardCon.Resize();
        }
        break;
    case WM_CHAR:
        if (KeyBoardCon.WM_char(wParam, tempTest))
        {
            MainGraph.BeginDraw();
            KeyBoardCon.DrawUpdate(5.76, true);
            MainGraph.EndDraw();
        }
        break;
    case WM_KEYDOWN:
        if (KeyBoardCon.WM_keydown(wParam, tempTest))
        {
            MainGraph.BeginDraw();
            KeyBoardCon.DrawUpdate(5.76, false);
            MainGraph.EndDraw();
        }
        break;
    case WM_DESTROY:
        {
            MainGraph.GraphicObject.DestroyG_Resources();
            PostQuitMessage(0);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
