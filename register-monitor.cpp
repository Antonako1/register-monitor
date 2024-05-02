// register-monitor.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "register-monitor.h"
#include <iostream>

#define MAX_LOADSTRING 100

extern "C" {
    uint32_t __stdcall testFun();
    uint32_t __stdcall getEaxR();
    uint32_t __stdcall getEbxR();
    uint32_t __stdcall getEcxR();
    uint32_t __stdcall getEdxR();
    uint32_t __stdcall getEsiR();
    uint32_t __stdcall getEdiR();
    uint32_t __stdcall getEbpR();
    uint32_t __stdcall getEspR();
}
uint32_t oldEax = 0,
        oldEbx = 0,
        oldEcx = 0,
        oldEdx = 0,
        oldEsi = 0,
        oldEdi = 0,
        oldEbp = 0,
        oldEsp = 0;

uint32_t currEax = 0,
        currEbx = 0,
        currEcx = 0,
        currEdx = 0,
        currEsi = 0,
        currEdi = 0,
        currEbp = 0,
        currEsp = 0;

void readRegisters() {
	oldEax = getEaxR();
	oldEbx = getEbxR();
	oldEcx = getEcxR();
	oldEdx = getEdxR();
	oldEsi = getEsiR();
	oldEdi = getEdiR();
	oldEbp = getEbpR();
	oldEsp = getEspR();
}

void readRegistersNew() {
    currEax = getEaxR();
    currEbx = getEbxR();
    currEcx = getEcxR();
    currEdx = getEdxR();
    currEsi = getEsiR();
    currEdi = getEdiR();
    currEbp = getEbpR();
    currEsp = getEspR();
}

void validate(HWND hWnd) {
    readRegistersNew();
    WCHAR buffer[64] = {};  // Adjust size as needed
    readRegistersNew();


    if (currEax != oldEax) {
        swprintf_s(buffer, L"Eax changed from %08X to %08X\n", oldEax, currEax);
        OutputDebugStringW(buffer);
        oldEax = currEax; // Update previous value
    }
    if (currEbx != oldEbx) {
        //MessageBox(hWnd, L"Register EBX has changed!", L"Register Change Detected", MB_OK | MB_ICONINFORMATION);
        swprintf_s(buffer, L"Ebx changed from %08X to %08X\n", oldEbx, currEbx);
        OutputDebugStringW(buffer);
        oldEbx = currEbx; // Update previous value
    }
    if (currEcx != oldEcx) {
        //MessageBox(hWnd, L"Register ECX has changed!", L"Register Change Detected", MB_OK | MB_ICONINFORMATION);
        swprintf_s(buffer, L"Ecx changed from %08X to %08X\n", oldEcx, currEcx);
        OutputDebugStringW(buffer);
        oldEcx = currEcx; // Update previous value
    }
    if (currEdx != oldEdx) {
        //MessageBox(hWnd, L"Register EDX has changed!", L"Register Change Detected", MB_OK | MB_ICONINFORMATION);
        swprintf_s(buffer, L"Edx changed from %08X to %08X\n", oldEdx, currEdx);
        OutputDebugStringW(buffer);
        oldEdx = currEdx; // Update previous value
    }
    if (currEsi != oldEsi) {
        //MessageBox(hWnd, L"Register ESI has changed!", L"Register Change Detected", MB_OK | MB_ICONINFORMATION);
        swprintf_s(buffer, L"Esi changed from %08X to %08X\n", oldEsi, currEsi);
        OutputDebugStringW(buffer);
        oldEsi = currEsi; // Update previous value
    }
    if (currEdi != oldEdi) {
        //MessageBox(hWnd, L"Register EDI has changed!", L"Register Change Detected", MB_OK | MB_ICONINFORMATION);
        swprintf_s(buffer, L"Edi changed from %08X to %08X\n", oldEdi, currEdi);
        OutputDebugStringW(buffer);
        oldEdi = currEdi; // Update previous value
    }
    if (currEbp != oldEbp) {
        //MessageBox(hWnd, L"Register EBP has changed!", L"Register Change Detected", MB_OK | MB_ICONINFORMATION);
        swprintf_s(buffer, L"Ebp changed from %08X to %08X\n", oldEbp, currEbp);
        OutputDebugStringW(buffer);
        oldEbp = currEbp; // Update previous value
    }
    if (currEsp != oldEsp) {
        //MessageBox(hWnd, L"Register ESP has changed!", L"Register Change Detected", MB_OK | MB_ICONINFORMATION);
        swprintf_s(buffer, L"Esp changed from %08X to %08X\n", oldEsp, currEsp);
        OutputDebugStringW(buffer);
        oldEsp = currEsp; // Update previous value
    }

}

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

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_REGISTERMONITOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    readRegisters();
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REGISTERMONITOR));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REGISTERMONITOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_REGISTERMONITOR);
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
    CW_USEDEFAULT, 0, 300, 300, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   SetTimer(hWnd, 1,100, NULL);


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
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
        validate(hWnd);

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rect;
            GetClientRect(hWnd, &rect);
            int y = 10;
            WCHAR textBuffer[64]= {};    
            SYSTEMTIME st, lt;

            GetSystemTime(&st);
            GetLocalTime(&lt);
            swprintf_s(textBuffer, L"Current time is: %02d:%02d:%02d", lt.wHour, lt.wMinute, lt.wSecond);
            rect.top = y;
            DrawText(hdc, textBuffer, -1, &rect, DT_LEFT | DT_TOP);
            y+=20;
            swprintf_s(textBuffer, L"EAX: %08X", oldEax);
            rect.top = y;
		    DrawText(hdc, textBuffer, -1, &rect, DT_LEFT | DT_TOP);
            y+=20;
            swprintf_s(textBuffer, L"EBX: %08X", oldEbx);
            rect.top = y;
            DrawText(hdc, textBuffer, -1, &rect, DT_LEFT | DT_TOP);
            y+=20;
            swprintf_s(textBuffer, L"ECX: %08X", oldEcx);
            rect.top = y;
            DrawText(hdc, textBuffer, -1, &rect, DT_LEFT | DT_TOP);
            y+=20;
            swprintf_s(textBuffer, L"EDX: %08X", oldEdx);
            rect.top = y;
            DrawText(hdc, textBuffer, -1, &rect, DT_LEFT | DT_TOP);
            y+=20;
            swprintf_s(textBuffer, L"ESI: %08X", oldEsi);
            rect.top = y;
            DrawText(hdc, textBuffer, -1, &rect, DT_LEFT | DT_TOP);
            y+=20;
            swprintf_s(textBuffer, L"EDI: %08X", oldEdi);
            rect.top = y;
            DrawText(hdc, textBuffer, -1, &rect, DT_LEFT | DT_TOP);
            y+=20;
            swprintf_s(textBuffer, L"EBP: %08X", oldEbp);
            rect.top = y;
            DrawText(hdc, textBuffer, -1, &rect, DT_LEFT | DT_TOP);
            y+=20;
            swprintf_s(textBuffer, L"ESP: %08X", oldEsp);
            rect.top = y;
            DrawText(hdc, textBuffer, -1, &rect, DT_LEFT | DT_TOP);


            EndPaint(hWnd, &ps);
        }
        break;
    case WM_TIMER:
		//MessageBox(hWnd, L"Mouse move detected!", L"Mouse Move", MB_OK | MB_ICONINFORMATION);
        InvalidateRect(hWnd, NULL, TRUE);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
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
