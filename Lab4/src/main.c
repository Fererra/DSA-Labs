#include <windows.h>

#define WIDTH 600
#define HEIGHT 450
#define K1 0.6
#define K2 0.68

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void drawGraph(HWND, HDC, PAINTSTRUCT, double, int);
void drawCondensationGraph(HWND, HDC, PAINTSTRUCT, double, int);

char ProgName[] = "Lab 4";

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

  HWND hWnd, btnDir, btnUndir, btnMod, btnCond;
  MSG lpMsg;

  hWnd = CreateWindow(
    ProgName,
    "Lab 4",
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

  btnDir = CreateWindow(
    "BUTTON",
    "Directed graph",
    WS_VISIBLE | WS_CHILD | WS_BORDER,
    400, 125,
    140, 30, 
    hWnd, (HMENU)1, NULL, NULL);

  btnUndir = CreateWindow(
    "BUTTON",
    "Undirected graph",
    WS_VISIBLE | WS_CHILD | WS_BORDER,
    400, 175, 
    140, 30, 
    hWnd, (HMENU)2, NULL, NULL);

  btnMod = CreateWindow(
    "BUTTON",
    "Modified graph",
    WS_VISIBLE | WS_CHILD | WS_BORDER,
    400, 225,
    140, 30,
    hWnd, (HMENU)3, NULL, NULL);

  btnCond = CreateWindow(
    "BUTTON",
    "Condensation graph",
    WS_VISIBLE | WS_CHILD | WS_BORDER,
    400, 275, 
    140, 30,
    hWnd, (HMENU)4, NULL, NULL);
  
  if (hWnd == NULL || btnDir == NULL || btnUndir == NULL 
    || btnMod == NULL || btnCond == NULL) {
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
  HDC hdc;
  PAINTSTRUCT ps;

  static int currentGraphType = 1;

  RECT rect = {0, 0, WIDTH, HEIGHT};

  switch (messg) {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);

      FillRect(hdc, &rect, WHITE_BRUSH);
      if (currentGraphType == 1) drawGraph(hWnd, hdc, ps, K1, 1);
      if (currentGraphType == 2) drawGraph(hWnd, hdc, ps, K1, 0);
      if (currentGraphType == 3) drawGraph(hWnd, hdc, ps, K2, 1);
      if (currentGraphType == 4) drawCondensationGraph(hWnd, hdc, ps, K2, 1);
      
      EndPaint(hWnd, &ps);
      break;

    case WM_COMMAND:
      switch (LOWORD(wParam)) {
        case 1:
          currentGraphType = 1;
          break;
        case 2:
          currentGraphType = 2;
          break;
        case 3:
          currentGraphType = 3;
          break;
        case 4:
          currentGraphType = 4;
          break;
        default:
          break;
      }

      InvalidateRect(hWnd, NULL, TRUE);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return(DefWindowProc(hWnd, messg, wParam, lParam));
  }
}