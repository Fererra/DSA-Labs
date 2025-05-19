#ifndef DRAWING_H
#define DRAWING_H

#define N 12
#define RADIUS 25
#define START 75

void drawLoop(HDC, int, int, int);
void drawStraightEdge(HDC, int, int, int, int, int);
void drawSideArc(HDC, int, int, int, int, int);
void drawTopBottomArc(HDC, int, int, int, int, int);
void drawCurvedEdge(HDC, int, int, int, int, int);
void drawEdge(HDC, int, int, int, int, int, int, int, int, int);
void drawVertex(HDC, int, int, int);
void drawGraph(HWND, HDC, PAINTSTRUCT, Graph*);
void drawPart(HWND, HDC, PAINTSTRUCT, int*);

#endif