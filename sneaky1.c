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

void initMap(char[MAX_ROW][MAX_COL]);
int randomInt(int);

void placeObstacles(char[MAX_ROW][MAX_COL]);
void printMap(char[MAX_ROW][MAX_COL]);

int canPlaceObstacle(char[MAX_ROW][MAX_COL], int, int);
int main(){
  char map[MAX_ROW][MAX_COL];


  //seed the random number generator
  srand(time(NULL));

  //initialize and print map
  initMap(map);
  placeObstacles(map);
  printMap(map);
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