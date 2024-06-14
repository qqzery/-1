#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MINES 10
#define EMPTY_CELL ' '

char grid[SIZE][SIZE];
char visibleGrid[SIZE][SIZE];

void initializeGrids() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = EMPTY_CELL;
            visibleGrid[i][j] = EMPTY_CELL;
        }
    }
}

void printGrid() {
    printf("   ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("--");
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d| ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", visibleGrid[i][j]);
        }
        printf("\n");
    }
}

void placeMines() {
    int count = 0;
    while (count < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (grid[x][y] != '*') {
            grid[x][y] = '*';
            count++;
        }
    }
}

int countAdjacentMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && grid[newX][newY] == '*') {
                count++;
            }
        }
    }
    return count;
}

void reveal(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || visibleGrid[x][y] != EMPTY_CELL) {
        return;
    }
    int count = countAdjacentMines(x, y);
    visibleGrid[x][y] = count + '0';
    if (count == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newX = x + i;
                int newY = y + j;
                if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && grid[newX][newY] != '*') {
                    reveal(newX, newY);
                }
            }
        }
    }
}

int checkGameStatus() {
    int revealedCount = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == '*' && visibleGrid[i][j] == '*') {
                return -1; // Game over (mine is revealed)
            }
            if (grid[i][j] != '*' && visibleGrid[i][j] != EMPTY_CELL) {
                revealedCount++;
            }
        }
    }
    if (revealedCount == SIZE * SIZE - MINES) {
        return 1; // You win (all non-mine cells are revealed)
    }
    return 0; // Game is still ongoing
}

int main() {
    srand(time(NULL));
    initializeGrids();
    placeMines();
    printGrid();

    int x, y;
    while (1) {
        printf("Enter coordinates (row and column) to reveal: ");
        scanf("%d %d", &x, &y);

        if (grid[x][y] == '*') {
            printf("Game Over! You hit a mine.\n");
            break;
        }
        else {
            reveal(x, y);
            printGrid();
        }

        int gameStatus = checkGameStatus();
        if (gameStatus == 1) {
            printf("Congratulations! You win!\n");
            break;
        }
        else if (gameStatus == -1) {
            printf("Game Over! You hit a mine.\n");
            break;
        }
    }

    return 0;
}
