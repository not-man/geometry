#ifndef GEOMETRY_H
#define GEOMETRY_H


#define GRID_WIDTH 40

#define GRID_HEIGHT 20

#define EMPTY_CELL '.'

#define FILLED_CELL '#'

#define FILL_CELL '*'

#define TRIANGLE_VERTEX_COUNT 3

#define FOUR_CONNECTED 4

#define EIGHT_CONNECTED 8

#define INPUT_LENGTH 128

#define OUTPUT_FILE "grid.pgm"



#define MENU_EXIT -1

#define MENU_LINE 1

#define MENU_TRIANGLE 2

#define MENU_FLOOD_FILL 3

#define MENU_SCANLINE_FILL 4

#define MENU_COMPARE_FILL 5

#define MENU_COMPARE_LINES 6

#define MENU_DEMO_FILL 7

#define MENU_SAVE 8

#define MENU_OPEN 9

#define MENU_DELETEPGM 10

#define DEMO_LEFT_X 10

#define DEMO_RIGHT_X 30

#define DEMO_BASE_Y 3

#define DEMO_TOP_X 20

#define DEMO_TOP_Y 13

#define DEMO_SEED_X 20

#define DEMO_SEED_Y 5
typedef struct point_s {

    int x;

    int y;

} point;
int max(int value1, int value2);

int OpenPgm();
int DeletePGM();

int readNumber(const char *prompt, int *value);

int readPoint(const char *prompt, point *currentPoint);

void clearGrid(char canvas[GRID_HEIGHT][GRID_WIDTH]);

void copyGrid(char destination[GRID_HEIGHT][GRID_WIDTH], char source[GRID_HEIGHT][GRID_WIDTH]);

void printGrid(char canvas[GRID_HEIGHT][GRID_WIDTH]);

int drawLine(point currentPoint, point endPoint, char canvas[GRID_HEIGHT][GRID_WIDTH]);

int drawDdaLine(point startPoint, point endPoint, char canvas[GRID_HEIGHT][GRID_WIDTH]);

int isTriangleValid(point vertexList[TRIANGLE_VERTEX_COUNT]);

void drawTriangle(point vertexList[TRIANGLE_VERTEX_COUNT], char canvas[GRID_HEIGHT][GRID_WIDTH]);

int isPointInsideContour(point seed, point vertexList[TRIANGLE_VERTEX_COUNT], char canvas[GRID_HEIGHT][GRID_WIDTH]);

int fillArea(int currentY, int currentX, int connectivity, char canvas[GRID_HEIGHT][GRID_WIDTH]);

int fillScanline(point vertexList[TRIANGLE_VERTEX_COUNT], char canvas[GRID_HEIGHT][GRID_WIDTH]);

int countDifferentCells(char first[GRID_HEIGHT][GRID_WIDTH], char second[GRID_HEIGHT][GRID_WIDTH]);

int savePgm(char canvas[GRID_HEIGHT][GRID_WIDTH]);

void showFillDemo(char canvas[GRID_HEIGHT][GRID_WIDTH]);
#endif
