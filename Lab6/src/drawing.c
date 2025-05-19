#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../headers/matrix_utils.h"
#include "../headers/coords_utils.h"
#include "../headers/dataStructures.h"
#include "../headers/kruskal.h"
#include "../headers/drawing.h"

int radius = RADIUS, dtx = 5;

void drawLoop(HDC hdc, int x, int y, int weight) {
    int indent = radius * 2.5;
    Ellipse(hdc, x - indent, y - indent, x, y);
    
    char buf[10];
    sprintf(buf, "%d", weight);

    int textX = x - indent - 10;
    int textY = y - indent - 10;

    TextOut(hdc, textX, textY, buf, strlen(buf));
}

void drawStraightEdge(HDC hdc, int x1, int y1, int x2, int y2, int weight) {
    double dx = abs(x1 - x2);
    double dy = abs(y1 - y2);

    int textX = (x1 + x2) / 2;
    int textY = (y1 + y2) / 2;

    char buf[10];
    sprintf(buf, "%d", weight);

    double fi, tanFi;
    int ax, ay;

    if (x1 == x2) {
        fi = y2 > y1 ? -90 : 90;
        ay = y2 > y1 ? -radius : radius;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        TextOut(hdc, textX - 10, textY, buf, strlen(buf));
    }

    if (y1 == y2) {
        fi = x2 > x1 ? 0 : 180;
        ax = x2 > x1 ? -radius : radius;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        TextOut(hdc, textX, textY - 10, buf, strlen(buf));
    } else if (x1 > x2) {
        if (dx > dy) {
            tanFi = dx / dy;
            fi = y1 > y2
                ? 90 + atan(tanFi) * 180 / 3.1416
                : 270 - atan(tanFi) * 180 / 3.1416;
            ay = radius / sqrt(1 + tanFi * tanFi);
            ax = ay * tanFi;
        } else {
            tanFi = dy / dx;
            fi = y1 > y2
                ? 180 - atan(tanFi) * 180 / 3.1416
                : 180 + atan(tanFi) * 180 / 3.1416;
            ax = radius / sqrt(1 + tanFi * tanFi);
            ay = ax * tanFi;

            textY += 15; 
        }

        ay = y1 < y2 ? -ay : ay;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2 + ax, y2 + ay);
        TextOut(hdc, textX - 15, textY, buf, strlen(buf));
    } else if (x2 > x1) {
        if (dx > dy) {
            tanFi = dx / dy;
            fi = y2 > y1
                ? atan(tanFi) * 180 / 3.1416 - 90
                : 90 - atan(tanFi) * 180 / 3.1416;
            ay = radius / sqrt(1 + tanFi * tanFi);
            ax = ay * tanFi;
        } else {
            tanFi = dy / dx;
            fi = y2 > y1
                ? -(atan(tanFi) * 180 / 3.1416)
                : atan(tanFi) * 180 / 3.1416;
            ax = radius / sqrt(1 + tanFi * tanFi);
            ay = ax * tanFi;

            textX -= 15;
        }

        ay = y2 > y1 ? -ay : ay;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2 - ax, y2 + ay);
        TextOut(hdc, textX, textY - 15, buf, strlen(buf));
    }
}

void drawSideArc(HDC hdc, int x, int y1, int y2, int isLeft, int weight) {
    double cx = isLeft ? x - radius * 2 : x + radius * 2;
    double cy = (y1 + y2) / 2;

    POINT pts[3] = {
        {x, y1},
        {cx, cy},
        {x, y2}
    };

    double dx = abs(cx - x);
    double dy = abs(cy - y2);

    double tanFi = isLeft ? dx / dy : dy / dx;
    double fi = isLeft
        ? 90 - (atan(tanFi) * 180 / 3.1416)
        : atan(tanFi) * 180 / 3.1416 - 180;

    int a = radius / sqrt(1 + tanFi * tanFi);
    int ax = isLeft ? a * tanFi : a;
    int ay = isLeft ? a : a * tanFi;

    Polyline(hdc, pts, 3);

    char buf[10];
    sprintf(buf, "%d", weight);

    int textX = (int)cx + (isLeft ? 10 : -10);
    int textY = (int)cy - 10;

    TextOut(hdc, textX, textY, buf, strlen(buf));
}

void drawTopBottomArc(HDC hdc, int y, int x1, int x2, int isTop, int weight) {
    double cx = (x1 + x2) / 2;
    double cy = isTop ? y - radius * 2 : y + radius * 2;

    POINT pts[3] = {
        {x1, y},
        {cx, cy},
        {x2, y}
    };

    double dx = abs(cx - x2);
    double dy = abs(cy - y);

    double tanFi = isTop ? dy / dx : dx / dy;
    double fi = isTop
        ? atan(tanFi) * 180 / 3.1416 - 180
        : 90 - (atan(tanFi) * 180 / 3.1416);

    int a = radius / sqrt(1 + tanFi * tanFi);
    int ax = isTop ? a : a * tanFi;
    int ay = isTop ? a * tanFi : a;

    Polyline(hdc, pts, 3);

    char buf[10];
    sprintf(buf, "%d", weight);

    int textX = (int)cx - 10;
    int textY = (int)cy + (isTop ? -10 : 5);

    TextOut(hdc, textX, textY, buf, strlen(buf)); 
}

void drawCurvedEdge(HDC hdc, int x1, int y1, int x2, int y2, int weight) {
    int offset = 50;
    double dx, dy;
    double fi, tanFi;
    int ax, ay;

    double cx = (x1 + x2) / 2.0;
    double cy = (y1 + y2) / 2.0;

    int textX = (int)cx;
    int textY = (int)cy;

    if (y1 == y2) {
        drawTopBottomArc(hdc, y1, x1, x2, x1 > x2, 1);
        return;
    } else if (x1 == x2) {
        drawSideArc(hdc, x1, y1, y2, y1 > y2, 1);
        return;
    }

    if (x1 > x2) {
        cx += offset;
        cy = y1 > y2 ? cy - offset : cy + offset;

        dx = abs(cx - x2);
        dy = abs(cy - y2);

        if (dx > dy) {
            tanFi = dx / dy;
            fi = y1 > y2
                ? 90 + atan(tanFi) * 180 / 3.1416
                : 270 - atan(tanFi) * 180 / 3.1416;
            ay = radius / sqrt(1 + tanFi * tanFi);
            ax = ay * tanFi;
        } else {
            tanFi = dy / dx;
            fi = y1 > y2
                ? 180 - atan(tanFi) * 180 / 3.1416
                : 180 + atan(tanFi) * 180 / 3.1416;
            ax = radius / sqrt(1 + tanFi * tanFi);
            ay = ax * tanFi;

            textY += 40;
        }

        textX += 60;
        ay = y2 > y1 ? -ay : ay;
    } else if (x2 > x1) {
        cx -= offset;
        cy = y1 > y2 ? cy - offset : cy + offset;

        dx = abs(cx - x2);
        dy = abs(cy - y2);

        if (dx > dy) {
            tanFi = dx / dy;
            fi = y1 < y2
                ? atan(tanFi) * 180 / 3.1416 - 90
                : 90 - atan(tanFi) * 180 / 3.1416;
            ay = radius / sqrt(1 + tanFi * tanFi);
            ax = ay * tanFi;
        } else {
            tanFi = dy / dx;
            fi = y1 < y2
                ? -(atan(tanFi) * 180 / 3.1416)
                : atan(tanFi) * 180 / 3.1416;
            ax = radius / sqrt(1 + tanFi * tanFi);
            ay = ax * tanFi;
        }

        ay = y2 > y1 ? -ay : ay;
    }

    POINT pts[3] = {
        {x1, y1},
        {(int)cx, (int)cy},
        {x2, y2}
    };

    Polyline(hdc, pts, 3);

    char buf[10];
    sprintf(buf, "%d", weight);

    TextOut(hdc, textX, textY, buf, strlen(buf));
}

void drawVertex(HDC hdc, int x, int y, int j) {
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    char nn[3];
    sprintf(nn, "%d", j + 1);
    TextOut(hdc, x - dtx, y - radius / 2, nn, strlen(nn));
};

void drawEdge(HDC hdc, int i, int j, int x1, int y1, int x2, int y2, int centerX, int centerY, int weight) {
    int cx = (x1 + x2) / 2;
    int cy = (y1 + y2) / 2;

    int crossesCenter = (cx == centerX && cy == centerY);

    if (abs(i - j) == 1) {
        drawStraightEdge(hdc, x1, y1, x2, y2, weight);
    } else if (x1 == x2) {
        drawSideArc(hdc, x1, y1, y2, y1 > y2, weight);
    } else if (y1 == y2) {
        drawTopBottomArc(hdc, y1, x1, x2, x1 > x2, weight);
    } else if (crossesCenter) {
        drawCurvedEdge(hdc, x1, y1, x2, y2, weight);
    } else {
        drawStraightEdge(hdc, x1, y1, x2, y2, weight);
    }
}

void drawGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, Graph *graph) {
    if (!graph) return;

    int n = graph->vertexCount;
    int **coords = getCoords(START);
    int centerX = findAverage(START, coords[0]);
    int centerY = findAverage(START, coords[1]);

    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    SelectObject(hdc, KPen);

    Vertex *v = graph->vertices;
    while (v) {
        Edge *e = v->edges;
        while (e) {
            if (v->id == e->dest) {
                int x = coords[0][v->id];
                int y = coords[1][v->id];
                drawLoop(hdc, x, y, e->weight);
            } else if (v->id < e->dest) {
                int x1 = coords[0][v->id];
                int y1 = coords[1][v->id];
                int x2 = coords[0][e->dest];
                int y2 = coords[1][e->dest];
                drawEdge(hdc, v->id, e->dest, x1, y1, x2, y2, centerX, centerY, e->weight);
            }
            e = e->next;
        }
        v = v->next;
    }

    SelectObject(hdc, BPen);
    v = graph->vertices;
    while (v) {
        int x = coords[0][v->id];
        int y = coords[1][v->id];
        drawVertex(hdc, x, y, v->id);
        v = v->next;
    }

    freeCoords(coords);
}

void drawPart(HWND hWnd, HDC hdc, PAINTSTRUCT ps, int *step) {
    if (*step > mstSize) return;

    int u = mstEdges[*step - 1].u;
    int v = mstEdges[*step - 1].v;
    int w = mstEdges[*step - 1].weight;

    int **coords = getCoords(START);
    int x1 = coords[0][u];
    int y1 = coords[1][u];
    int x2 = coords[0][v];
    int y2 = coords[1][v];
    int centerX = findAverage(START, coords[0]);
    int centerY = findAverage(START, coords[1]);

    HPEN GPen = CreatePen(PS_SOLID, 3, RGB(0, 200, 0));
    SelectObject(hdc, GPen);

    drawEdge(hdc, u, v, x1, y1, x2, y2, centerX, centerY, w);
    drawVertex(hdc, x1, y1, u);
    drawVertex(hdc, x2, y2, v);

    freeCoords(coords);
}
