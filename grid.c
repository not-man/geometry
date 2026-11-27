#include <stdio.h>
#include "geometry.h"

void clearGrid(char canvas[GRID_HEIGHT][GRID_WIDTH]) {
    int row;
    int column;

    for (row = 0; row < GRID_HEIGHT; row++) {

        for (column = 0; column < GRID_WIDTH; column++) {

            canvas[row][column] = EMPTY_CELL;

        }

    }

}

void copyGrid(char destination[GRID_HEIGHT][GRID_WIDTH], char source[GRID_HEIGHT][GRID_WIDTH]) {
    int row;
    int column;

    for (row = 0; row < GRID_HEIGHT; row++) {

        for (column = 0; column < GRID_WIDTH; column++) {

            destination[row][column] = source[row][column];

        }

    }

}

void printGrid(char canvas[GRID_HEIGHT][GRID_WIDTH]) {
    int row;
    int column;

    for (row = GRID_HEIGHT - 1; row >= 0; row--) {

        for (column = 0; column < GRID_WIDTH; column++) {

            printf("%c ", canvas[row][column]);

        }

        printf("\n");

    }

}

int countDifferentCells(char first[GRID_HEIGHT][GRID_WIDTH], char second[GRID_HEIGHT][GRID_WIDTH]) {
    int row;
    int column;

    int pixelCount = 0;

    for (row = 0; row < GRID_HEIGHT; row++) {

        for (column = 0; column < GRID_WIDTH; column++) {

            if (first[row][column] != second[row][column]) {

                pixelCount++;

            }

        }

    }

    return pixelCount;

}
