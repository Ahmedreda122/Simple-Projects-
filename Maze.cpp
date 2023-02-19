#include <iostream>

using namespace std;

//Maze size
#define N 6

// The Token that represents the shape of your movement print.
#define TOKEN 'v'

void print(char arr[N][N]);
void Copy(char arr1[N][N], char arr2[N][N]);
void solveMaze(char maze[N][N], int i, int j);
char bestSol[N][N];

template<typename type>
int Count(type arr[N][N], type value);


int main()
{
  // the maze format
  char maze[N][N] = 
  {
    {' ','O','O',' ',' ',' '},
    {' ',' ',' ',' ','O',' '},
    {'O',' ',' ',' ',' ',' '},
    {' ',' ',' ','O','O','O'},
    {' ','O',' ',' ',' ',' '},
    {' ','O','O',' ','O',' '}
  };
  // Solving the maze (Getting all possible routes)
  solveMaze(maze, 0 , 0);

  
  cout << "The Best Route: \n";
  //Printing the Best Route ever
  print(bestSol);
}

void solveMaze(char maze[N][N], int i, int j)
{
  static int bestCounter = N*N;

  if (i == N-1 && j == N-1)
  {
    // Counting the Number of TOKENS(value) in the maze (array)
    int counter = Count<char>(maze, TOKEN);
    // find the best solution by finding the shortest path(minimum number of TOKENS or moves in the maze board)
    if (counter < bestCounter)
    {
      bestCounter = counter;
      // Copy maze board into bestSol board
      Copy(bestSol, maze);
    }
    // Printing the solution
    cout << endl;
    print(maze);
    cout << endl;
    return;
  }

  // Mark the start point
  if (i == 0 && j == 0)
  {
    maze[i][j] = TOKEN;
  }

  // move right
  if ( j != N - 1 && maze[i][j + 1] == ' ')
  {
    maze[i][j + 1] = TOKEN;
    solveMaze(maze, i, j + 1);
    maze[i][j + 1] = ' ';
  }
  //move left
  if (j != 0)
  {
    if (maze[i][j - 1] == ' ')
    {
      maze[i][j - 1] = TOKEN;
      solveMaze(maze, i, j - 1);
      maze[i][j - 1] = ' ';
    }
  }
  // move Down
  if (i != N - 1 && maze[i + 1][j] == ' ')
  {
    maze[i + 1][j] = TOKEN;
    solveMaze(maze, i + 1, j);
    maze[i + 1][j] = ' ';
  }
  // move up
  if (i != 0 && maze[i - 1][j] == ' ')
  {
    maze[i - 1][j] = TOKEN;
    solveMaze(maze, i - 1, j);
    maze[i - 1][j] = ' ';
  }
  return;
}

void print(char arr[N][N])
{
  cout << "------------\n";
  for (int i = 0; i < N; i++)
  {
    for(int j = 0; j < N; j++)
    {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
  cout << "------------\n";
}

void Copy(char arr1[N][N], char arr2[N][N])
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      arr1[i][j] = arr2[i][j];
    }
  }
  return;
} 

template<typename type>
int Count(type arr[N][N], type value)
{
  int counter = 0;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (arr[i][j] == value)
      {
        ++counter;
      }
    }
  }
  return counter;
}
