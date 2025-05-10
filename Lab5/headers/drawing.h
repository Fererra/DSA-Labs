#ifndef DRAWING_H
#define DRAWING_H

#define N 12
#define RADIUS 16
#define START 50

void arrow(HDC, float, int, int);
void drawLoop(HDC, int, int, int);
void drawStraightEdge(HDC, int, int, int, int, int);
void drawSideArc(HDC, int, int, int, int, int);
void drawTopBottomArc(HDC, int, int, int, int, int);
void drawCurvedEdge(HDC, int, int, int, int, int);
void drawEdge(HDC, int, int, int, int, int, int, int, int, int);
void drawVertex(HDC, int, int, int);
void drawGraph(HWND, HDC, PAINTSTRUCT, int);
void drawGraphTraversal(HWND, HDC, PAINTSTRUCT, int*, int);

#endif