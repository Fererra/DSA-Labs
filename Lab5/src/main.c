#include <windows.h>
#include <stdio.h>

#define N 12
#define WIDTH 575
#define HEIGHT 675

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void drawGraph(HWND, HDC, PAINTSTRUCT, int);
void drawGraphTraversal(HWND, HDC, PAINTSTRUCT, int*, int);

char ProgName[] = "Lab 5";
int step;

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

  HWND hWnd, btnBFS, btnDFS;
  MSG lpMsg;

  hWnd = CreateWindow(
    ProgName,
    "Lab 5",
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

  btnBFS = CreateWindow(
    "BUTTON",
    "BFS",
    WS_VISIBLE | WS_CHILD | WS_BORDER,
    150, 525,
    120, 30, 
    hWnd, (HMENU)1, NULL, NULL);

  btnDFS = CreateWindow(
    "BUTTON",
    "DFS",
    WS_VISIBLE | WS_CHILD | WS_BORDER,
    300, 525, 
    120, 30, 
    hWnd, (HMENU)2, NULL, NULL);
  
  if (hWnd == NULL || btnBFS == NULL || btnDFS == NULL) {
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

void removeButton(HWND hWnd, int num) {
  DestroyWindow(GetDlgItem(hWnd, num));
}

void createButton(HINSTANCE hInstance, HWND hWnd, char name[], HMENU num) {
  CreateWindow("BUTTON", name, WS_VISIBLE | WS_CHILD | WS_BORDER, 225, 525, 120, 30, (HWND)hWnd, (HMENU)num, (HINSTANCE)hInstance, (HINSTANCE)NULL);
}

void printMethodInfo(HDC hdc, char methodName[]) {
  char formattedText[100];

  TextOut(hdc, 152, 570, "Blue - New Vertex. Orange - Current Vertex", 42);
  sprintf(formattedText, "Green - Visited Vertex and %s-Tree Edge", methodName);
  TextOut(hdc, 155, 590, formattedText, strlen(formattedText));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
  HDC hdc;
  PAINTSTRUCT ps;
  HINSTANCE hInstance;

  RECT rect = {0, 0, WIDTH, HEIGHT};

  switch (messg) {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);

      FillRect(hdc, &rect, WHITE_BRUSH);
      drawGraph(hWnd, hdc, ps, 1);
      
      EndPaint(hWnd, &ps);
      break;

    case WM_COMMAND:
      hdc = GetDC(hWnd);
      switch (LOWORD(wParam)) {
        case 1:
          step = 0;
          removeButton(hWnd, 1);
          removeButton(hWnd, 2);
          createButton(hInstance, hWnd, "Next", (HMENU)3);
          printMethodInfo(hdc, "BFS");
          drawGraphTraversal(hWnd, hdc, ps, &step, 1);
          step++;
          break;
        case 2:
          step = 0;
          removeButton(hWnd, 1);
          removeButton(hWnd, 2);
          createButton(hInstance, hWnd, "Next", (HMENU)4);
          printMethodInfo(hdc, "DFS");
          drawGraphTraversal(hWnd, hdc, ps, &step, 0);
          step++;
          break;
        case 3:
          drawGraphTraversal(hWnd, hdc, ps, &step, 1);
          if (step == N) removeButton(hWnd, 3);
          step++;
          break;
        case 4:
          drawGraphTraversal(hWnd, hdc, ps, &step, 0);
          if (step == N) removeButton(hWnd, 4);
          step++;
          break;
        default:
          break;
      }
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return(DefWindowProc(hWnd, messg, wParam, lParam));
  }
}