#include <iostream>

using namespace std;


void change_me(int * x)
{
  cin >> *x;
}


int main()
{
  /* pointers
     pointers as arrays
     using pointers to make 2d arrays
  */

  int * array = new int[10];
  /*
    new keyword allocates 10 integer slots
    how big is an integer? 32 bits = 4 bytes
    40 bytes
   */
  
  for (int i = 0; i < 10; i++)
  {
    array[i] = i + 1;
    cout << i << " " << array[i] << endl;
  }

  // if you declare a block of memory and not just one int *, then use the [] brackets to delete.  
  delete [] array;

  int * p = new int;
  *p = 5;
  cout << *p << endl;
  delete p;

  char * new_pointer = nullptr;
  // random code in here
  if (new_pointer)
  {
    cout << new_pointer << endl;
  }
  
  
  int y = 10;
  change_me(&y);
  cout << y << endl;

  /*

    2d arrays;

    Secretly a 2d array is really just an array of 1-d arrays;
    we need a double pointer.
    let's create a 3x3 array for tic-tac-toe purposes. 
  */

  int ** tictactoe = new int*[3];

  /*
    64 bit OS = 8 bytes is a pointer
    
    tictactoe = 0x24
    [ 0x60 ] int * 
    [ 0x100 ] int *
    [ ---- ] int *

    0x60 tictactoe[0] = [int, int, int]
    we still need to make the rows we have three uninitialized pointers sitting there.  
   */
  tictactoe[0] = new int[3]; // 0th row
  tictactoe[1] = new int[3]; // 1st row
  tictactoe[2] = new int[3]; // 2nd row

  for (int i = 0; i < 3; i++)
    cout << tictactoe[i] << endl;
  
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      tictactoe[row][col] = 0;

  for(int row = 0; row < 3; row++)
  {
    for(int col = 0; col < 3; col++)
    {
      cout << tictactoe[row][col] << " ";
    }
    cout << endl;
  }


  for (int kill = 0; kill < 3; kill++)
    delete [] tictactoe[kill];
  
  delete [] tictactoe;

  
  
  return 0;
}
