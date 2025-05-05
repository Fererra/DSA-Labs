#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../headers/matrix_utils.h"
#include "../headers/coords_utils.h"
#include "../headers/drawing.h"

int radius = RADIUS, dtx = 5;

void arrow(HDC hdc, float fi, int px, int py) {
    fi = 3.1416 * (180.0 - fi) / 180.0;
    int lx, ly, rx, ry;
    lx = px + 15 * cos(fi + 0.3);
    rx = px + 15 * cos(fi - 0.3);
    ly = py + 15 * sin(fi + 0.3);
    ry = py + 15 * sin(fi - 0.3);
    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
}

void drawLoop(HDC hdc, int x, int y, int isDirected) {
    int indent = radius * 2.5;
    Ellipse(hdc, x - indent, y - indent, x, y);
    if (isDirected) arrow(hdc, 280, x, y - radius);
}

void drawStraightEdge(HDC hdc, int x1, int y1, int x2, int y2, int isDirected) {
    double dx = abs(x1 - x2);
    double dy = abs(y1 - y2);

    double fi, tanFi;
    int ax, ay;

    if (x1 == x2) {
        fi = y2 > y1 ? -90 : 90;
        ay = y2 > y1 ? -radius : radius;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        if (isDirected) arrow(hdc, fi, x2, y2 + ay);
    }

    if (y1 == y2) {
        fi = x2 > x1 ? 0 : 180;
        ax = x2 > x1 ? -radius : radius;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        if (isDirected) arrow(hdc, fi, x2 + ax, y2);
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
        }

        ay = y1 < y2 ? -ay : ay;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2 + ax, y2 + ay);
        if (isDirected) arrow(hdc, fi, x2 + ax, y2 + ay);
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
        }

        ay = y2 > y1 ? -ay : ay;
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2 - ax, y2 + ay);
        if (isDirected) arrow(hdc, fi, x2 - ax, y2 + ay);
    }
}

void drawSideArc(HDC hdc, int x, int y1, int y2, int isLeft, int isDirected) {

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

    if (isDirected) {
        if (isLeft) {
            arrow(hdc, fi, x - ax, y2 + ay);
        } else {
            arrow(hdc, fi, x + ax, y2 - ay);
        }
    }
}

void drawTopBottomArc(HDC hdc, int y, int x1, int x2, int isTop, int isDirected) {

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
    if (isDirected) {
        if (isTop) {
            arrow(hdc, fi, x2 + ax, y - ay);
        } else {
            arrow(hdc, fi, x2 - ax, y + ay);
        }
    }
}

void drawCurvedEdge(HDC hdc, int x1, int y1, int x2, int y2, int isDirected) {
    int offset = 25;
    double dx, dy;
    double fi, tanFi;
    int ax, ay;

    double cx = (x1 + x2) / 2.0;
    double cy = (y1 + y2) / 2.0;

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
        }

        ay = y2 > y1 ? -ay : ay;

        if (isDirected) arrow(hdc, fi, x2 + ax, y2 + ay);
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

        if (isDirected) arrow(hdc, fi, x2 - ax, y2 + ay);
    }

    POINT pts[3] = {
        {x1, y1},
        {(int)cx, (int)cy},
        {x2, y2}
    };

    Polyline(hdc, pts, 3);
}

void drawEdge(HDC hdc, int i, int j, int x1, int y1, int x2, int y2, int centerX, int centerY, int isDirected) {
    int cx = (x1 + x2) / 2;
    int cy = (y1 + y2) / 2;

    int crossesCenter = (cx == centerX && cy == centerY);

    if (abs(i - j) == 1) {
        drawStraightEdge(hdc, x1, y1, x2, y2, isDirected);
    } else if (x1 == x2) {
        drawSideArc(hdc, x1, y1, y2, y1 > y2, isDirected);
    } else if (y1 == y2) {
        drawTopBottomArc(hdc, y1, x1, x2, x1 > x2, isDirected);
    } else if (crossesCenter) {
        drawCurvedEdge(hdc, x1, y1, x2, y2, isDirected);
    } else {
        drawStraightEdge(hdc, x1, y1, x2, y2, isDirected);
    }
}

void drawGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, double K, int isDirected) {
    int n = N;
    int **coords = getCoords(START);
    int centerX = findAverage(START, coords[0]);
    int centerY = findAverage(START, coords[1]); 
    int **matrix = isDirected ? generateAdir(K) : generateAundir(K);

    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));

    SelectObject(hdc, KPen);

    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 1) {
            drawLoop(hdc, coords[0][i], coords[1][i], isDirected);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && i != j) {
                int x1 = coords[0][i];
                int y1 = coords[1][i];
                int x2 = coords[0][j];
                int y2 = coords[1][j];

                if (matrix[j][i] && isDirected) {
                    drawCurvedEdge(hdc, x1, y1, x2, y2, 1);
                } else {
                    if (!isDirected && j < i) {
                        continue;
                    }
                    drawEdge(hdc, i, j, x1, y1, x2, y2, centerX, centerY, isDirected);
                }
            }
        }
    }

    SelectObject(hdc, BPen);
    for (int j = 0; j < n; j++) {
        int x = coords[0][j];
        int y = coords[1][j];
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
        char nn[3];
        sprintf(nn, "%d", j + 1);
        TextOut(hdc, x - dtx, y - radius / 2, nn, strlen(nn));
    }
    
    freeCoords(coords);
}

void drawCondensationGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, double K, int isDirected) {
    int componentCount;
    int n = N;
    int **coords = getCoords(START);
    int centerX = findAverage(START, coords[0]);
    int centerY = findAverage(START, coords[1]); 
    int **matrix = generateAcondensationByK(K, &componentCount);

    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));

    SelectObject(hdc, KPen);

    for (int i = 0; i < componentCount; i++) {
        for (int j = 0; j < componentCount; j++) {
            if (matrix[i][j] == 1 && i != j) {
                int x1 = coords[0][i];
                int y1 = coords[1][i];
                int x2 = coords[0][j];
                int y2 = coords[1][j];

                if (matrix[j][i] && isDirected) {
                    drawCurvedEdge(hdc, x1, y1, x2, y2, 1);
                } else {
                    if (!isDirected && j < i) {
                        continue;
                    }
                    drawEdge(hdc, i, j, x1, y1, x2, y2, centerX, centerY, isDirected);
                }
            }
        }
    }

    SelectObject(hdc, BPen);
    for (int j = 0; j < componentCount; j++) {
        int x = coords[0][j];
        int y = coords[1][j];
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
        char nn[3];
        sprintf(nn, "%d", j + 1);
        TextOut(hdc, x - dtx, y - radius / 2, nn, strlen(nn));
    }
    
    freeCoords(coords);
};
