// TP_winda.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "framework.h"
#include "TP_winda.h"
#include "winda.h"
#define MAX_LOADSTRING 100
//stałe

UINT CZAS = 33;
const int PRZYCISKI_ID[20]{ 1,2,3,4,10,12,13,14,20,21,23,24,30,31,32,34,40,41,42,43};
// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego
WINDA winda;

// Przekaż dalej deklaracje funkcji dołączone w tym module kodu:
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

    // TODO: W tym miejscu umieść kod.

    // Inicjuj ciągi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TPWINDA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    // Wykonaj inicjowanie aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TPWINDA));

    MSG msg;

    // Główna pętla komunikatów:
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

void Rysunek(HDC hdc) {
    Graphics graphics(hdc);
    Pen pen(Color(255, 0, 0, 0), 4);
    for (int i = 0; i < 5; i++) {
        if (i % 2) {
            graphics.DrawLine(&pen, 480, DLUGOSC_PIETRA * (i + 1), 720, DLUGOSC_PIETRA * (i + 1));
        }
        else {
            graphics.DrawLine(&pen, 10, DLUGOSC_PIETRA * (i + 1), 230, DLUGOSC_PIETRA * (i + 1));
        }
    }
    for (int i = 0; i < 5; i++) {
        for (auto& osoba : winda.napietrach[i]) {
            Bitmap PersonImg(L"person.png");
            Rect PersonSpace(osoba.GetX(), osoba.GetY(), PersonImg.GetWidth() / 2, PersonImg.GetHeight() / 2);
            graphics.DrawImage(&PersonImg, PersonSpace);
        }
    }
    for (auto& osoba : winda.osobywwindzie) {
        Bitmap PersonImg(L"person.png");
        Rect PersonSpace(osoba.GetX(), osoba.GetY(), PersonImg.GetWidth() / 2, PersonImg.GetHeight() / 2);
        graphics.DrawImage(&PersonImg, PersonSpace);
    }

    graphics.DrawLine(&pen, 230, winda.getY(), 480, winda.getY());
    graphics.DrawLine(&pen, 480, winda.getY() - 80, 480, winda.getY() - winda.GetDoorOffset());
    graphics.DrawLine(&pen, 230, winda.getY() - 80, 230, winda.getY() - winda.GetDoorOffset());
    graphics.DrawLine(&pen, 230, winda.getY() - 80, 480, winda.getY() - 80);
    //sciany stale
    graphics.DrawLine(&pen, 480, 0, 480, 100);
    graphics.DrawLine(&pen, 480, 200, 480, 300);
    graphics.DrawLine(&pen, 480, 400, 480, 500);

    graphics.DrawLine(&pen, 230, DLUGOSC_PIETRA, 230, DLUGOSC_PIETRA*2);
    graphics.DrawLine(&pen, 230, DLUGOSC_PIETRA*3, 230, DLUGOSC_PIETRA*4);
    graphics.DrawLine(&pen, 228, 500, 483, 500);
    //napisy
    int waga = winda.GetWeight();
    TextOut(hdc, 500, 10, L"Waga:", 5);
    wchar_t buffer[256];
    if (waga == 0) {
        TextOut(hdc, 545, 10, L"0", 1);
    }
    else {
        wsprintfW(buffer, L"%d", waga);
        int liczba_cyfr = floor(log10(waga) + 1);
        TextOut(hdc, 545, 10, buffer, liczba_cyfr);
    }
   

}


//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TPWINDA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TPWINDA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Przechowuj dojście wystąpienia w naszej zmiennej globalnej

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   //kreator przycisków
   for (int pietro = 0; pietro < 5; pietro++) {
       for (int cel = 0; cel < 5; cel++) {
           if (pietro == cel) continue;
           int x = (pietro % 2 == 0) ? 10: 700;
           int y = abs(pietro - 4)*100 + abs(cel-4) *20;
           wchar_t buffer[256];
           wsprintfW(buffer, L"%d", (cel));
           HWND hwndButton = CreateWindow(
               L"BUTTON",  // Predefined class; Unicode assumed 
               buffer,      // Button text 
               WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
               x,         // x position 
               y,         // y position 
               20,        // Button width
               20,        // Button height
               hWnd,     // Parent window
               (HMENU)(pietro*10 + cel),       // pierwsza cyfra pietro, druga cel. 
               (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
               NULL);      // Pointer not needed
       }
   }
   HWND RestartButton = CreateWindow(
       L"BUTTON",  // Predefined class; Unicode assumed 
       L"Restart",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
       500,         // x position 
       30,         // y position 
       60,        // Button width
       20,        // Button height
       hWnd,     // Parent window
       (HMENU)ID_RESTART,       // pierwsza cyfra pietro, druga cel. 
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);      // Pointer not needed

   SetTimer(hWnd, 1, CZAS, NULL);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna głównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno główne
//  WM_DESTROY  - opublikuj komunikat o wyjściu i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            for (auto ID : PRZYCISKI_ID) {
                if (wmId == ID) winda.request(ID);
            }
            // Analizuj zaznaczenia menu:
            switch (wmId)
            {
            case ID_RESTART:
                winda.Restart();
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
        //from https://www.robertelder.ca/doublebuffering/
        RECT Client_Rect;
        GetClientRect(hWnd, &Client_Rect);
        int win_width = Client_Rect.right - Client_Rect.left;
        int win_height = Client_Rect.bottom + Client_Rect.left;
        PAINTSTRUCT ps;
        HDC Memhdc;
        HDC hdc;
        HBITMAP Membitmap;
        hdc = BeginPaint(hWnd, &ps);
        Memhdc = CreateCompatibleDC(hdc);
        Membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
        SelectObject(Memhdc, Membitmap);
        //drawing code goes in here
        FillRect(Memhdc, &Client_Rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
        Rysunek(Memhdc);
        BitBlt(hdc, 0, 0, win_width, win_height, Memhdc, 0, 0, SRCCOPY);
        DeleteObject(Membitmap);
        DeleteDC(Memhdc);
        DeleteDC(hdc);
        EndPaint(hWnd, &ps);
        }
        break;
    case WM_ERASEBKGND:
    {
        return 1;
    }
    case WM_TIMER: {
        winda.NastepnaAkcja();
        InvalidateRect(hWnd, NULL, true);
    }break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Procedura obsługi komunikatów dla okna informacji o programie.
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
