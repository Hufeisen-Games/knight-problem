#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int toIndex(int x, int y, int size);
int isValid(int x, int y, bool* visited, int size);
bool solveKnightTour(int x, int y, int moveCount, bool* visited, int size);

int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

int main(void) {

    int size = 8;

    bool* visited = malloc(sizeof(bool) * size * size);
    if (visited == NULL) {
        printf("Not enough memory!");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size * size; i++) {
        visited[i] = 0;
    }

    bool is_solved = solveKnightTour(0, 0, 0, visited, size);

    if (is_solved) {
        printf("Path found!");
    } else {
        printf("No path found!");
    }

    free(visited);
    return EXIT_SUCCESS;
}

/**
 * @brief Check if there is a valid knight tour on the board with the given size. Good luck and hopefully enough time if you try size > 7.
 * @param x x param to continue tour
 * @param y y param to continue tour
 * @param moveCount current move count
 * @param visited array to keep track of visited fields
 * @param size chessboard length
 * @return true when knight tour solved
 */
bool solveKnightTour(int x, int y, int moveCount, bool* visited, int size) {
    printf("Solving move %d\n", moveCount);

    if (moveCount == size * size) {
        return true;
    }

    if (!isValid(x, y, visited, size)) {
        return false;
    }

    visited[toIndex(x, y, size)] = 1;

    for (int move = 0; move < 8; move++) {
        int next_x = x + dx[move];
        int next_y = y + dy[move];
        if (solveKnightTour(next_x, next_y, moveCount+1, visited, size)) { return true; }
    }

    visited[toIndex(x, y, size)] = 0;
    return false;
}

/**
 * @brief Converts coordinates into index in one dimensional array
 * @param x x coordinate, between 0 and size - 1
 * @param y y coordinate, between 0 and size - 1
 * @param size size of coordinate axis, must be bigger than 0
 * @return index in array, -1 when incorrect input params
 */
int toIndex(int x, int y, int size) {
    if (size <= 0 || x < 0 || x >= size || y < 0 || y >= size) { return -1; }
    return x + y * size;
}

/**
 * @brief Check if coordinate is in the chessboard and was not visited before
 * @param x x coordinate, between 0 and size - 1
 * @param y y coordinate, between 0 and size - 1
 * @param visited 1d bool array consisting of visit information, must be size*size-1 big
 * @param size size of coordinate axis, must be bigger than 0
 * @return true if move is valid, otherwise false
 */
int isValid(int x, int y, bool* visited, int size) {

    int index = toIndex(x, y, size);
    if (index == -1) { return 0; }
    return !visited[index];
}