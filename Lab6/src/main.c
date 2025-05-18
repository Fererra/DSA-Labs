#include <windows.h>
#include <stdio.h>
#include "../headers/kruskal.h"

#define N 12
#define WIDTH 755
#define HEIGHT 825           

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void drawGraph(HWND, HDC, PAINTSTRUCT);
void drawPart(HWND, HDC, PAINTSTRUCT, int*);

char ProgName[] = "Lab 6";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
  WNDCLASS w;

  w.lpszClassName = ProgName;
  w.hInstance = hInstance;
  w.lpfnWndProc = WndProc;
  w.hCursor = LoadCursor(NULL, IDC_ARROW);
  w.hIcon = 0;
  w.lpszMenuName = 0;
  w.hbrBackground = WHITE_BRUSH;
  w.style = CS_HREDRAW | CS_VREDRAW;
  w.cbClsExtra = 0;
  w.cbWndExtra = 0;

  if (!RegisterClass(&w)) return 0;

  HWND hWnd, btnNext;
  MSG lpMsg;

  hWnd = CreateWindow(
    ProgName,
    "Lab 6",
    WS_OVERLAPPEDWINDOW,
    10,
    10,
    WIDTH,
    HEIGHT,
    (HWND)NULL,
    (HMENU)NULL,
    (HINSTANCE)hInstance,
    (HINSTANCE)NULL
  );

  btnNext = CreateWindow(
    "BUTTON",
    "Next",
    WS_VISIBLE | WS_CHILD | WS_BORDER,
    290, 725,
    170, 30, 
    hWnd, (HMENU)1, NULL, NULL);
  
  if (hWnd == NULL || btnNext == NULL) {
      return 0;
  }

  ShowWindow(hWnd, nCmdShow);

  int b;

  while ((b = GetMessage(&lpMsg, hWnd, 0, 0)) != 0) {
    if (b == -1) return lpMsg.wParam;

    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
  }

  return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
    static int step = 1;
    static int initialized = 0;

    HDC hdc;
    PAINTSTRUCT ps;

    RECT rect = {0, 0, WIDTH, HEIGHT};

    switch (messg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);

            FillRect(hdc, &rect, WHITE_BRUSH);
            drawGraph(hWnd, hdc, ps);

            if (!initialized) {
                prepareMST();
                initialized = 1;
            }

            EndPaint(hWnd, &ps);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                hdc = GetDC(hWnd);
                drawPart(hWnd, hdc, ps, &step);
                if (step == mstSize) DestroyWindow(GetDlgItem(hWnd, 1));
                step++;
                ReleaseDC(hWnd, hdc);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, messg, wParam, lParam);
    }

    return 0;
}
