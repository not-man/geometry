#include <stdio.h>
#include "geometry.h"

int fillArea(int currentY, int currentX, int connectivity, char canvas[GRID_HEIGHT][GRID_WIDTH]) {

    if (currentX < 0 || currentX >= GRID_WIDTH || currentY < 0 || currentY >= GRID_HEIGHT || canvas[currentY][currentX] != EMPTY_CELL) {

        return 0;

    }


    canvas[currentY][currentX] = FILL_CELL;

    int pixelCount = 1;


    pixelCount += fillArea(currentY + 1, currentX, connectivity, canvas);

    pixelCount += fillArea(currentY, currentX + 1, connectivity, canvas);

    pixelCount += fillArea(currentY - 1, currentX, connectivity, canvas);

    pixelCount += fillArea(currentY, currentX - 1, connectivity, canvas);


    if (connectivity == EIGHT_CONNECTED) {

        pixelCount += fillArea(currentY + 1, currentX + 1, connectivity, canvas);

        pixelCount += fillArea(currentY + 1, currentX - 1, connectivity, canvas);

        pixelCount += fillArea(currentY - 1, currentX + 1, connectivity, canvas);

        pixelCount += fillArea(currentY - 1, currentX - 1, connectivity, canvas);

    }

    return pixelCount;

}

int fillScanline(point vertexList[TRIANGLE_VERTEX_COUNT], char canvas[GRID_HEIGHT][GRID_WIDTH]) {

    int pixelCount = 0;
    int row;
    int vertexIndex;
    int column;
    double intersection[2];
    int intersectionCount;
    point startPoint;
    point endPoint;
    int lowY;
    int highY;
    double left;
    double right;

    for (row = 0; row < GRID_HEIGHT; row++) {


        intersectionCount = 0;



        for (vertexIndex = 0; vertexIndex < TRIANGLE_VERTEX_COUNT; vertexIndex++) {

            startPoint = vertexList[vertexIndex];

            endPoint = vertexList[(vertexIndex + 1) % TRIANGLE_VERTEX_COUNT];

            lowY = startPoint.y < endPoint.y ? startPoint.y : endPoint.y;

            highY = startPoint.y > endPoint.y ? startPoint.y : endPoint.y;

            if (row >= lowY && row < highY) {

                intersection[intersectionCount] = startPoint.x + (double)(row - startPoint.y) * (endPoint.x - startPoint.x) / (endPoint.y - startPoint.y);

                intersectionCount++;

            }

        }

        if (intersectionCount == 2) {

            left = intersection[0] < intersection[1] ? intersection[0] : intersection[1];

            right = intersection[0] > intersection[1] ? intersection[0] : intersection[1];



            for (column = 0; column < GRID_WIDTH; column++) {

                if (column > left && column < right && canvas[row][column] == EMPTY_CELL) {

                    canvas[row][column] = FILL_CELL;

                    pixelCount++;

                }

            }

        }

    }

    return pixelCount;

}

void showFillDemo(char canvas[GRID_HEIGHT][GRID_WIDTH]) {

    point vertexList[TRIANGLE_VERTEX_COUNT] = {

        {DEMO_LEFT_X, DEMO_BASE_Y},

        {DEMO_RIGHT_X, DEMO_BASE_Y},

        {DEMO_TOP_X, DEMO_TOP_Y}

    };

    char fourGrid[GRID_HEIGHT][GRID_WIDTH];

    char eightGrid[GRID_HEIGHT][GRID_WIDTH];

    drawTriangle(vertexList, fourGrid);

    copyGrid(eightGrid, fourGrid);

    int fourCount = fillArea(DEMO_SEED_Y, DEMO_SEED_X, FOUR_CONNECTED, fourGrid);

    int eightCount = fillArea(DEMO_SEED_Y, DEMO_SEED_X, EIGHT_CONNECTED, eightGrid);

    printf("4-connected, filled pixels: %d\n", fourCount);

    printGrid(fourGrid);

    printf("8-connected, filled pixels: %d\n", eightCount);

    printGrid(eightGrid);

    printf("different cells: %d\n", countDifferentCells(fourGrid, eightGrid));

    copyGrid(canvas, eightGrid);

}
