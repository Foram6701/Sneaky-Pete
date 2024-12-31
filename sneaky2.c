#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAX_ROW 15
#define MAX_COL 60

#define NUM_OBSTACLES 5
#define OBSTACLE_WIDTH 5
#define OBSTACLE_HEIGHT 4

#define C_TRUE 1
#define C_FALSE 0

// Pete will be represented as 'P'
#define PETE 'P'

//functions from sneaky1.c
void initMap(char[MAX_ROW][MAX_COL]);
int randomInt(int);

void placeObstacles(char[MAX_ROW][MAX_COL]);
void printMap(char[MAX_ROW][MAX_COL]);

int canPlaceObstacle(char[MAX_ROW][MAX_COL], int, int);

// New functions for sneaky2.c
int canMove(char[MAX_ROW][MAX_COL], int, int);
void updatePetePosition(char[MAX_ROW][MAX_COL], int*, int*);
int sneaky2main();

int main(){
  char map[MAX_ROW][MAX_COL];


  //seed the random number generator
  srand(time(NULL));

  //initialize and print map
  initMap(map);
  placeObstacles(map);
  printMap(map);

  sneaky2main();
  return 0;
}
/*
  Function:  randomInt
  Purpose:   returns a random number in the range [0,max)
  Parameters:
    in:      maximum of range
    return:  randomly generated number
*/

int randomInt(int max)
{
  return (rand() % max);
}


/*
* You should end up with something like this 
* when printed in the console (but bigger):
* -------------------------------
* |                             |
* |                             |
* |                             |
* |                             |
* |                             |
* |                             |
* -------------------------------
*
* The obstacles would be placed inside the box somewhere.
*/
void initMap(char map[MAX_ROW][MAX_COL])
{
  for (int i = 0; i < MAX_ROW; i++)
  {
    // if first or last row, fill with '-'
    if (i == 0 || i == MAX_ROW-1)
    {
      for (int j = 0; j < MAX_COL; j++)
      {
        map[i][j] = '-';
      }
    }else {
      // fill first and last column with '|'
      map[i][0] = '|';
      map[i][MAX_COL-1] = '|';
    
      // fill every other column in the row with ' '
      for (int j = 1; j < MAX_COL-1; j++)
      {
        map[i][j] = ' ';
      }
    }
  }
}
/*
  Function:  placeObstacles
  Purpose:   Randomly places obstacles of fixed size in the map without overlap.
  Parameters:
    in/out:  map - 2D char array representing the prison grounds
  Logic:
    - Randomly generate starting row and column for each obstacle.
    - Use canPlaceObstacle to check if there's enough space.
    - Place the obstacle if possible, increment the obstacle counter.
*/
/*
  Function:  canPlaceObstacle
  Purpose:   Determines if an obstacle can be placed at a specific position.
  Parameters:
    in:      map - 2D char array representing the prison grounds
    in:      row - starting row of the obstacle
    in:      col - starting column of the obstacle
  return:    C_TRUE (1) if the obstacle can be placed, C_FALSE (0) otherwise
  Logic:
    - Check if all positions within the obstacle's dimensions are empty (' ').
*/
int canPlaceObstacle(char map[MAX_ROW][MAX_COL], int row, int col) {
    for (int i = 0; i < OBSTACLE_HEIGHT; i++) {
        for (int j = 0; j < OBSTACLE_WIDTH; j++) {
            if (map[row + i][col + j] != ' ') {
                return C_FALSE; 
                // can't place if already occupied
            }
        }
    }
    return C_TRUE;
}
/*
  Function:  placeObstacles
  Purpose:   Randomly places obstacles of fixed size in the map without overlap.
  Parameters:
    in/out:  map - 2D char array representing the prison grounds
  Logic:
    - Randomly generate starting row and column for each obstacle.
    - Use canPlaceObstacle to check if there's enough space.
    - Place the obstacle if possible, increment the obstacle counter.
*/
void placeObstacles(char map[MAX_ROW][MAX_COL]) {
    int obstaclesPlaced = 0;
    while (obstaclesPlaced < NUM_OBSTACLES) {
        int row = randomInt(MAX_ROW - OBSTACLE_HEIGHT - 2) + 1;  // adjust to fit obstacle
        int col = randomInt(MAX_COL - OBSTACLE_WIDTH - 2) + 1;   // adjust to fit obstacle

        if (canPlaceObstacle(map, row, col)) {
            for (int i = 0; i < OBSTACLE_HEIGHT; i++) {
                for (int j = 0; j < OBSTACLE_WIDTH; j++) {
                    map[row + i][col + j] = '0' + obstaclesPlaced; // '0', '1', '2', etc.
                }
            }
            obstaclesPlaced++;
        }
    }
}
/*
  Function:  printMap
  Purpose:   Prints the map with borders and placed obstacles to the console.
  Parameters:
    in:      map - 2D char array representing the prison grounds
  Logic:
    - Loops through the map and prints each character.
*/
void printMap(char map[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
int sneaky2main() {
    char map[MAX_ROW][MAX_COL];

    // Seed the random number generator
    srand(time(NULL));

    // Initialize and print the map
    initMap(map);
    placeObstacles(map);

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
        if (peteCol == MAX_COL - 2) {  // Check if Pete reached the last column
            printf("Sneaky Pete escaped!\n");
    break;  // Break out of the loop after printing the message
        }

    }

    return 0;
}


/*
  Function: canMove
  Purpose:  Checks if Pete can move to a specific position.
  Parameters:
    in:      map - 2D char array representing the prison grounds
    in:      row - row to move to
    in:      col - column to move to
  return:   C_TRUE if Pete can move, C_FALSE otherwise
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
  Parameters:
    in/out:  map - 2D char array representing the prison grounds
    in/out:  peteRow - current row of Pete (updated after move)
    in/out:  peteCol - current column of Pete (updated after move)
  Logic:
    - Tries to move Pete right first. If not possible, moves up or down.
    - Updates Pete's position on the map and erases the old one.
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
    else if (canMove(map, newRow, newCol - 1)) {
        newCol--;
    }
    // If all other directions are blocked, Pete stays in place

    // Update Pete's position on the map
    map[*peteRow][*peteCol] = ' ';   // Clear old position
    map[newRow][newCol] = PETE;      // Set new position

    // Update the row and column variables
    *peteRow = newRow;
    *peteCol = newCol;  // Ensure peteCol gets updated here
}