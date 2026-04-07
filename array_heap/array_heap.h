#ifndef __ARRAY_HEAP_H__
#define __ARRAY_HEAP_H__

#include <iostream>
#include <vector>

using namespace std;

// data types must be "comparable" = the < and = operator (also > probably) have to work. 
// a < b and b < c then a < c, a <= b and b <= a then a == b

class ArrayHeap
{
    public:
        ArrayHeap();
        void insert(int x);
        int getMax();
        int peekMax() const;
    private:
        void percolate_up(int index);
        void percolate_down(int index);
        vector<int> array;
        int heap_size;
};

#endif 

