#include <stdio.h>
#include "geometry.h"

int main(void) {

    point startPoint, endPoint, seed;

    point vertexList[TRIANGLE_VERTEX_COUNT];

    char canvas[GRID_HEIGHT][GRID_WIDTH];

    char otherCanvas[GRID_HEIGHT][GRID_WIDTH];

    int choice;

    int triangleReady = 0;
    int vertexIndex;
    int inputError;
    char prompt[INPUT_LENGTH];
    int connectivity;
    int pixelCount;
    int floodCount;
    int scanlineCount;



    clearGrid(canvas);



    while (1) {

        printf("1. line           2. triangle       3. flood fill  4. scanline fill\n");

        printf("5. compare fills  6. compare lines  7. fill demo\n");

        printf("8. save PGM       9. open PGM       10. delete PGM\n");
        
        printf("-1. exit\n");



        if (readNumber("choice: ", &choice) != 0) {

            if (feof(stdin)) {

                break;

            }

            continue;

        }

        if (choice == MENU_EXIT) {

            break;

        }



        switch (choice) {

            case MENU_LINE: {

                triangleReady = 0;

                if (readPoint("start x y: ", &startPoint) != 0 || readPoint("end x y: ", &endPoint) != 0) {

                    break;

                }

                clearGrid(canvas);

                pixelCount = drawLine(startPoint, endPoint, canvas);

                printGrid(canvas);

                printf("line pixels: %d, steps: %d\n", pixelCount, pixelCount - 1);

                break;

            }



            case MENU_TRIANGLE: {

                triangleReady = 0;

                inputError = 0;

                for (vertexIndex = 0; vertexIndex < TRIANGLE_VERTEX_COUNT && inputError == 0; vertexIndex++) {


                    snprintf(prompt, sizeof(prompt), "vertex %d x y: ", vertexIndex + 1);

                    inputError = readPoint(prompt, &vertexList[vertexIndex]);

                }

                if (inputError != 0) {

                    break;

                }

                if (!isTriangleValid(vertexList)) {

                    printf("triangle has no area\n");

                    break;

                }

                drawTriangle(vertexList, canvas);

                printGrid(canvas);

                triangleReady = 1;

                break;

            }



            case MENU_FLOOD_FILL: {

                if (!triangleReady) {

                    printf("the triangle has not been constructed\n");

                    break;

                }

                drawTriangle(vertexList, canvas);

                if (readPoint("seed x y: ", &seed) != 0) {

                    break;

                }

                if (!isPointInsideContour(seed, vertexList, canvas)) {

                    printf("point is outside triangle\n");

                    break;

                }


                if (readNumber("connectivity (4 or 8): ", &connectivity) != 0) {

                    break;

                }

                if (connectivity != FOUR_CONNECTED && connectivity != EIGHT_CONNECTED) {

                    printf("invalid choice\n");

                    break;

                }

                pixelCount = fillArea(seed.y, seed.x, connectivity, canvas);

                printGrid(canvas);

                printf("filled pixels: %d\n", pixelCount);

                break;

            }



            case MENU_SCANLINE_FILL: {

                if (!triangleReady) {

                    printf("the triangle has not been constructed\n");

                    break;

                }

                drawTriangle(vertexList, canvas);

                pixelCount = fillScanline(vertexList, canvas);

                printGrid(canvas);

                printf("filled pixels: %d\n", pixelCount);

                break;

            }



            case MENU_COMPARE_FILL: {

                if (!triangleReady) {

                    printf("the triangle has not been constructed\n");

                    break;

                }

                drawTriangle(vertexList, canvas);

                if (readPoint("seed x y: ", &seed) != 0) {

                    break;

                }

                if (!isPointInsideContour(seed, vertexList, canvas)) {

                    printf("point is outside triangle\n");

                    break;

                }

                copyGrid(otherCanvas, canvas);

                floodCount = fillArea(seed.y, seed.x, FOUR_CONNECTED, canvas);

                scanlineCount = fillScanline(vertexList, otherCanvas);

                printf("flood fill: %d pixels\n", floodCount);

                printGrid(canvas);

                printf("scanline fill: %d pixels\n", scanlineCount);

                printGrid(otherCanvas);

                printf("different cells: %d\n", countDifferentCells(canvas, otherCanvas));

                break;

            }



            case MENU_COMPARE_LINES: {

                triangleReady = 0;

                if (readPoint("start x y: ", &startPoint) != 0 || readPoint("end x y: ", &endPoint) != 0) {

                    break;

                }

                clearGrid(canvas);

                clearGrid(otherCanvas);

                pixelCount = drawLine(startPoint, endPoint, canvas);

                drawDdaLine(startPoint, endPoint, otherCanvas);

                printf("Bresenham:\n");

                printGrid(canvas);

                printf("DDA:\n");

                printGrid(otherCanvas);

                printf("line pixels: %d, steps: %d, different cells: %d\n", pixelCount, pixelCount - 1, countDifferentCells(canvas, otherCanvas));


                break;

            }



            case MENU_DEMO_FILL:

                triangleReady = 0;

                showFillDemo(canvas);

                break;



            case MENU_SAVE:

                savePgm(canvas);



                break;

            case MENU_OPEN:
                OpenPgm();
                break;
            
            case MENU_DELETEPGM:
                DeletePGM();
                break;
                
            default:

                printf("invalid choice\n");

        }

    }

    return 0;

}
