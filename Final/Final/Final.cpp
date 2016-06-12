// Final.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Final.h"
#include "Queap.h"

#pragma region DEFS
#define BTN_ADAUGA 0x01
#define BTN_STERGERE 0x02
#define BTN_RESETARE 0x03
#define BTN_MINIM 0x04
#pragma endregion


#define MAX_LOADSTRING 100
#define SECOND_TIMER 400
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Queap Q;
HWND textbox, buton, deleteBtn, info,label, resetBtn,minBtn;
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void processAdauga(HWND hWnd);
void procesareStergere(HWND hWnd);
void procesareMin(HWND hWnd);
void Draw(HDC hwnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FINAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FINAL));

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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FINAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FINAL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	HDC hdc;
    switch (message)
    {
	case WM_CREATE:
		init(&Q);
		//label = CreateWindow(L"STATIC", L"Introduceti datele ", WS_CHILD | WS_VISIBLE | SS_LEFT | ES_MULTILINE | WM_CTLCOLORSTATIC, 10, 40, 120, 30, hWnd, NULL, NULL, NULL);
		textbox = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 40, 200, 30, hWnd, NULL, NULL, NULL);
		buton = CreateWindow(L"BUTTON", L"Adaugare", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 80, 200, 30, hWnd, (HMENU)BTN_ADAUGA, NULL, NULL);
		deleteBtn = CreateWindow(L"BUTTON", L"Stergere", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 120, 200, 30, hWnd, (HMENU)BTN_STERGERE, NULL, NULL);
		resetBtn= CreateWindow(L"BUTTON", L"Reseteaza", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 160, 200, 30, hWnd, (HMENU)BTN_RESETARE, NULL, NULL);
		minBtn = CreateWindow(L"BUTTON", L"Minim", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 200, 200, 30, hWnd, (HMENU)BTN_MINIM, NULL, NULL);
    case WM_COMMAND:
        {
            wmId = LOWORD(wParam);
            switch (wmId)
            {
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				case BTN_ADAUGA:
				{
					processAdauga(hWnd);
					break;
				}
				case BTN_STERGERE:
				{
					procesareStergere(hWnd);
					break;
				}
				case BTN_MINIM:
				{
					procesareMin(hWnd);
				}
				case BTN_RESETARE:
				{
					Clean(&Q);
					init(&Q);
				}
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			Draw(hdc);
            EndPaint(hWnd, &ps);
			SetTimer(hWnd, SECOND_TIMER, SECOND_TIMER, NULL);
        }
        break;
	case WM_TIMER:
		if (wParam == SECOND_TIMER)
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

#pragma region Drawing_Area
void Draw(HDC hdc)
{
	// draw a line 
	HPEN hLinePen, hPenOld;
	COLORREF qLineColor = RGB(0, 0, 0);
	hLinePen = CreatePen(PS_SOLID, 2, qLineColor);
	hPenOld = (HPEN)SelectObject(hdc, hLinePen);
	MoveToEx(hdc, 250, 0, NULL);
	LineTo(hdc, 250, 1100);

	MoveToEx(hdc, 250, 150, NULL);
	LineTo(hdc, 2500, 150);


	SelectObject(hdc, hPenOld);
	DeleteObject(hLinePen);



	// draw specific elements of queap
	TextOut(hdc, 400, 40, L"Lista", 6);
	TextOut(hdc, 400, 80, L"k =", 4);
	TextOut(hdc, 400, 100,L"n =", 4);
	TextOut(hdc, 400, 200, L"Arbore", 7);
	int k = Q.k;
	int n = Q.n;
	
	char temp[20];
	wchar_t wc[20];
	_itoa(k, temp, 10);
	size_t cSize = strlen(temp) + 1;
	mbstowcs(wc, temp, cSize);

	TextOut(hdc, 425, 80, wc, cSize);
	_itoa(n, temp, 10);
	cSize = strlen(temp) + 1;
	mbstowcs(wc, temp, cSize);

	TextOut(hdc, 425, 100, wc, cSize);
    //drawinng the list  
	Afisare(Q.lista_inlantuita, hdc,500,50,40);
	// drawing the tree last
	Afisare(Q.queap_arbore->Radacina,0,0,hdc, 900, 200, 40);



}
#pragma endregion


#pragma region Commands_Area

void processAdauga(HWND hWnd)
{
	int len = GetWindowTextLength(textbox) + 1;
	wchar_t* text = new wchar_t[len];
	char temp[10];
	GetWindowText(textbox, text, len);
	int number;
	size_t out_len = wcstombs(temp, text, len);
	int no = atoi(temp);
	if (no != 0x00)
	{
		Insert(&Q, no);
	}
	DestroyWindow(textbox);
	textbox = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 40, 200, 30, hWnd, NULL, NULL, NULL);
}

void procesareStergere(HWND hWnd)
{
	int len = GetWindowTextLength(textbox) + 1;
	wchar_t* text = new wchar_t[len];
	char temp[10];
	GetWindowText(textbox, text, len);
	int number;
	size_t out_len = wcstombs(temp, text, len);
	int no = atoi(temp);
	Element*elm = NULL;
	if (no != 0x00)
	{
		elm = Stergere(&Q, no);
	}
	if (elm == NULL)
	{
		MessageBox(hWnd, L"Eroare la stergerea elementului", L"Eroare" ,MB_OK | MB_ICONEXCLAMATION);
	}
	DestroyWindow(textbox);
	textbox = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 40, 200, 30, hWnd, NULL, NULL, NULL);
}

void procesareMin(HWND hWnd)
{
	Element * elm = Minimum(&Q);
	int i = elm->value;
	char temp[20];
	wchar_t wc[20];
	_itoa(i, temp, 10);
	size_t cSize = strlen(temp) + 1;
	mbstowcs(wc, temp, cSize);

	wchar_t min[40] = L"Minim= ";
	wsprintfW(min + 7, L"%d", i);
	::MessageBox(hWnd, min, L"Minim", MB_OK | MB_ICONEXCLAMATION);
}
#pragma endregion
