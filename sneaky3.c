#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAX_ROW 15
#define MAX_COL 60

#define C_TRUE 1
#define C_FALSE 0

// Pete will be represented as 'P'
#define PETE 'P'

// Function prototypes
void initMap(char[MAX_ROW][MAX_COL]);
int randomInt(int);
void placeObstacles(char[MAX_ROW][MAX_COL], int obstacleHeight, int obstacleWidth, int numObstacles);
void printMap(char[MAX_ROW][MAX_COL]);
int canPlaceObstacle(char[MAX_ROW][MAX_COL], int row, int col, int obstacleHeight, int obstacleWidth);
int canMove(char[MAX_ROW][MAX_COL], int row, int col);
void updatePetePosition(char[MAX_ROW][MAX_COL], int* peteRow, int* peteCol);
int sneaky3main();

int main(){
    int obstacleHeight, obstacleWidth, numObstacles;
    
    // Ask the user for obstacle dimensions and number of obstacles
    printf("Enter obstacle height (1-10): ");
    scanf("%d", &obstacleHeight);
    printf("Enter obstacle width (1-10): ");
    scanf("%d", &obstacleWidth);
    printf("Enter number of obstacles (1-10): ");
    scanf("%d", &numObstacles);

    // Validate user input
    if (obstacleHeight < 1 || obstacleHeight > 10 || obstacleWidth < 1 || obstacleWidth > 10 || numObstacles < 1 || numObstacles > 10) {
        printf("Invalid input! Please enter values between 1 and 10.\n");
        return 1;
    }

    // Start the main game logic
    sneaky3main(obstacleHeight, obstacleWidth, numObstacles);
    return 0;
}

/*
  Function:  randomInt
  Purpose:   returns a random number in the range [0,max)
*/
int randomInt(int max) {
    return (rand() % max);
}

/*
  Function:  initMap
  Purpose:   Initializes the map with borders
*/
void initMap(char map[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; i++) {
        if (i == 0 || i == MAX_ROW-1) {
            for (int j = 0; j < MAX_COL; j++) {
                map[i][j] = '-';
            }
        } else {
            map[i][0] = '|';
            map[i][MAX_COL-1] = '|';
            for (int j = 1; j < MAX_COL-1; j++) {
                map[i][j] = ' ';
            }
        }
    }
}

/*
  Function:  canPlaceObstacle
  Purpose:   Determines if an obstacle can be placed at a specific position.
*/
int canPlaceObstacle(char map[MAX_ROW][MAX_COL], int row, int col, int obstacleHeight, int obstacleWidth) {
    // Check if the obstacle fits within the map boundaries
    if (row + obstacleHeight > MAX_ROW - 1 || col + obstacleWidth > MAX_COL - 1) {
        return C_FALSE;  // Obstacle doesn't fit within bounds
    }

    // Check if all positions within the obstacle's dimensions are empty
    for (int i = 0; i < obstacleHeight; i++) {
        for (int j = 0; j < obstacleWidth; j++) {
            if (map[row + i][col + j] != ' ') {
                return C_FALSE; 
            }
        }
    }
    return C_TRUE;
}

/*
  Function:  placeObstacles
  Purpose:   Randomly places obstacles of specified size in the map without overlap.
*/
void placeObstacles(char map[MAX_ROW][MAX_COL], int obstacleHeight, int obstacleWidth, int numObstacles) {
    int obstaclesPlaced = 0;
    while (obstaclesPlaced < numObstacles) {
        int row = randomInt(MAX_ROW - obstacleHeight - 2) + 1;  // Avoid top and bottom boundaries
        int col = randomInt(MAX_COL - obstacleWidth - 2) + 1;   // Avoid first and last columns

        if (canPlaceObstacle(map, row, col, obstacleHeight, obstacleWidth)) {
            for (int i = 0; i < obstacleHeight; i++) {
                for (int j = 0; j < obstacleWidth; j++) {
                    map[row + i][col + j] = '0' + obstaclesPlaced; // Use '0', '1', '2', etc.
                }
            }
            obstaclesPlaced++;
        }
    }
}

/*
  Function:  printMap
  Purpose:   Prints the map with borders and placed obstacles to the console.
*/
void printMap(char map[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

/*
  Function: sneaky3main
  Purpose:  Main game loop for Sneaky Pete, including obstacle placement.
*/
int sneaky3main(int obstacleHeight, int obstacleWidth, int numObstacles) {
    char map[MAX_ROW][MAX_COL];

    // Seed the random number generator
    srand(time(NULL));

    // Initialize and print the map
    initMap(map);
    placeObstacles(map, obstacleHeight, obstacleWidth, numObstacles);

    // Initialize Pete's starting position
    int peteRow = randomInt(MAX_ROW - 2) + 1;  // Random row (avoiding boundaries)
    int peteCol = 1;  // Start in the first empty column
    map[peteRow][peteCol] = PETE;

    // Game loop
    while (peteCol < MAX_COL - 1) {
        printMap(map);

        // Pause to control game pace
        usleep(100000);  // Sleep for 100 milliseconds

        // Move Pete and update his position
        updatePetePosition(map, &peteRow, &peteCol);

        // Check if Pete has escaped
        if (peteCol == MAX_COL - 2) {
            printf("Sneaky Pete escaped!\n");
            break;
        }
    }

    return 0;
}

/*
  Function: canMove
  Purpose:  Checks if Pete can move to a specific position.
*/
int canMove(char map[MAX_ROW][MAX_COL], int row, int col) {
    if (row < 1 || row >= MAX_ROW - 1 || col < 1 || col >= MAX_COL - 1) {
        return C_FALSE;  // Can't move into boundary
    }
    if (map[row][col] == ' ' || map[row][col] == PETE) {
        return C_TRUE;   // Move allowed if space is empty
    }
    return C_FALSE;      // Can't move into obstacles or any other character
}

/*
  Function: updatePetePosition
  Purpose:  Moves Pete on the map by one space based on a simple strategy.
*/
void updatePetePosition(char map[MAX_ROW][MAX_COL], int* peteRow, int* peteCol) {
    int newRow = *peteRow;
    int newCol = *peteCol;

    // Try to move right if possible
    if (canMove(map, newRow, newCol + 1)) {
        newCol++;
    }
    // If right is blocked, try moving up
    else if (canMove(map, newRow - 1, newCol)) {
        newRow--;
    }
    // If up is blocked, try moving down
    else if (canMove(map, newRow + 1, newCol)) {
        newRow++;
    }

    // Update Pete's position on the map
    map[*peteRow][*peteCol] = ' ';   // Clear old position
    map[newRow][newCol] = PETE;      // Set new position

    // Update the row and column variables
    *peteRow = newRow;
    *peteCol = newCol;
}
