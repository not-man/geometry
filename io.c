#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"

int readNumber(const char *prompt, int *value) {

    char input[INPUT_LENGTH];

    char extra;



    printf("%s", prompt);

    if (fgets(input, sizeof(input), stdin) == NULL) {

        return 1;

    }

    if (sscanf(input, "%d %c", value, &extra) != 1) {

        printf("invalid input\n");

        return 1;

    }

    return 0;

}

int readPoint(const char *prompt, point *currentPoint) {

    char input[INPUT_LENGTH];

    char extra;

    int x, y;



    printf("%s", prompt);

    if (fgets(input, sizeof(input), stdin) == NULL) {

        return 1;

    }

    if (sscanf(input, "%d %d %c", &x, &y, &extra) != 2) {

        printf("invalid input\n");

        return 1;

    }

    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {

        printf("out of range\n");

        return 1;

    }



    currentPoint->x = x;

    currentPoint->y = y;

    return 0;

}

int OpenPgm(){
    if(system("xdg-open grid.pgm")!=0){
        printf("PGM file not found\n");
        return 1;
    }
    return 0;
}

int DeletePGM(){
    if(remove("grid.pgm")!=0){
        printf("Error deleting file\n");
        return 1;
    }
    printf("File deleted\n");
    return 0;
}

int savePgm(char canvas[GRID_HEIGHT][GRID_WIDTH]) {
    int row;
    int column;
    int color;

    FILE *output = fopen(OUTPUT_FILE, "w");

    if (output == NULL) {

        printf("cannot save file\n");

        return 1;

    }



    fprintf(output, "P2\n%d %d\n255\n", GRID_WIDTH, GRID_HEIGHT);

    for (row = GRID_HEIGHT - 1; row >= 0; row--) {

        for (column = 0; column < GRID_WIDTH; column++) {

            color = 255;

            if ( canvas[row][column] == FILLED_CELL ) {

                color = 0;

            } else if (canvas[row][column] == FILL_CELL) {

                color = 128;

            }

            fprintf(output, "%d ", color);

        }

        fprintf(output, "\n");

    }

    fclose(output);

    printf("saved %s\n", OUTPUT_FILE);

    return 0;

}
