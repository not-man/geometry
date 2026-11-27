#include <stdlib.h>
#include "geometry.h"

int drawLine(point currentPoint, point endPoint, char canvas[GRID_HEIGHT][GRID_WIDTH]) {

    int deltaX = abs(endPoint.x - currentPoint.x);

    int deltaY = abs(endPoint.y - currentPoint.y);

    int stepX = endPoint.x < currentPoint.x ? -1 : 1;

    int stepY = endPoint.y < currentPoint.y ? -1 : 1;

    int stepCount = max(deltaX, deltaY);

    int decision;
    int pixelIndex;



    if (deltaX >= deltaY) {

        decision = 2 * deltaY - deltaX;

    } else {

        decision = 2 * deltaX - deltaY;

    }



    for (pixelIndex = 0; pixelIndex <= stepCount; pixelIndex++) {

        canvas[currentPoint.y][currentPoint.x] = FILLED_CELL;



        if (pixelIndex == stepCount) {

            break;

        }

        if (deltaX >= deltaY) {

            currentPoint.x += stepX;

            if (decision < 0) {

                decision += 2 * deltaY;

            } else {

                currentPoint.y += stepY;

                decision += 2 * deltaY - 2 * deltaX;

            }

        } else {

            currentPoint.y += stepY;

            if (decision < 0) {

                decision += 2 * deltaX;

            } else {

                currentPoint.x += stepX;

                decision += 2 * deltaX - 2 * deltaY;

            }

        }

    }

    return stepCount + 1;

}

int drawDdaLine(point startPoint, point endPoint, char canvas[GRID_HEIGHT][GRID_WIDTH]) {

    int deltaX = endPoint.x - startPoint.x;

    int deltaY = endPoint.y - startPoint.y;

    int stepCount = max(abs(deltaX), abs(deltaY));



    if (stepCount == 0) {

        canvas[startPoint.y][startPoint.x] = FILLED_CELL;

        return 1;

    }



    double xStep = (double)deltaX / stepCount;

    double yStep = (double)deltaY / stepCount;
    int pixelIndex;
    int x;
    int y;



    for (pixelIndex = 0; pixelIndex <= stepCount; pixelIndex++) {

        x = (int)(startPoint.x + pixelIndex * xStep + 0.5);

        y = (int)(startPoint.y + pixelIndex * yStep + 0.5);

        canvas[y][x] = FILLED_CELL;

    }

    return stepCount + 1;

}

int isTriangleValid(point vertexList[TRIANGLE_VERTEX_COUNT]) {

    int det = (vertexList[1].x - vertexList[0].x) * (vertexList[2].y - vertexList[0].y) - (vertexList[1].y - vertexList[0].y) * (vertexList[2].x - vertexList[0].x);

    return det != 0;

}

void drawTriangle(point vertexList[TRIANGLE_VERTEX_COUNT], char canvas[GRID_HEIGHT][GRID_WIDTH]) {
    int vertexIndex;

    clearGrid(canvas);

    for (vertexIndex = 0; vertexIndex < TRIANGLE_VERTEX_COUNT; vertexIndex++) {

        drawLine(vertexList[vertexIndex], vertexList[(vertexIndex + 1) % TRIANGLE_VERTEX_COUNT], canvas);

    }

}

int isPointInsideContour(point seed, point vertexList[TRIANGLE_VERTEX_COUNT], char canvas[GRID_HEIGHT][GRID_WIDTH]) {
    int vertexIndex;
    int hasPositive = 0;
    int hasNegative = 0;
    int crossProduct;
    point edgeStart;
    point edgeEnd;

    if (seed.x < 0 || seed.x >= GRID_WIDTH || seed.y < 0 || seed.y >= GRID_HEIGHT) {
        return 0;
    }

    if (canvas[seed.y][seed.x] != EMPTY_CELL) {
        return 0;
    }

    for (vertexIndex = 0; vertexIndex < TRIANGLE_VERTEX_COUNT; vertexIndex++) {

        edgeStart = vertexList[vertexIndex];
        edgeEnd = vertexList[(vertexIndex + 1) % TRIANGLE_VERTEX_COUNT];

        crossProduct =(edgeEnd.x - edgeStart.x) * (seed.y - edgeStart.y) - (edgeEnd.y - edgeStart.y) * (seed.x - edgeStart.x);

        if (crossProduct == 0) {
            return 0;
        }

        if (crossProduct > 0) {
            hasPositive = 1;
        } else {
            hasNegative = 1;
        }

        if (hasPositive && hasNegative) {
            return 0;
        }
    }

    return 1;
}
