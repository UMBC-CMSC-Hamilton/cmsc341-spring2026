#include <iostream>
#include <string>

#include "binary.h"

int main()
{
  string s;
  int x;
  cin >> s;
  BinarySearchTree<int> bst;
  while(s != "quit")
  {
    if(s == "insert")
    {
      cin >> x;
      bst.insert(x);
    }
    else if (s == "remove")
    {
      cin >> x;
      bst.remove(x);
    }

    bst.display();
    cin >> s;
  }
}
