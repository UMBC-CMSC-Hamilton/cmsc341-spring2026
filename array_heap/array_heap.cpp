#include "array_heap.h"

ArrayHeap::ArrayHeap()
    : heap_index(0)
{
    array.push_back(0); // garbage index 0 element, we never touch it. 
}

void ArrayHeap::insert(int x)
{
    if(heap_size < array.size())
    {
        array[heap_index + 1] = x;
        heap_index++;
    }
    else
    {
        array.push_back(x);
        heap_index++;
    }
    percolate_up(heap_index);
}

int ArrayHeap::getMax()
{
    int return_value = 0;
    if(heap_index >= 1)
    {
        return_value = array[1];
        array[1] = array[heap_index];
        heap_index--;

        percolate_down(1);

        return return_value;
    }
    else
    {
        throw std::out_of_range();
    }
}

int ArrayHeap::peekMax() const
{
    if(heap_index >= 1)
    {
        return array[1];
    }
    else
    {
        throw std::out_of_range();
    }
}

void ArrayHeap::percolate_up(int index)
{
    while(index > 0)
    {   // assuming it's a max heap
        if(array[index / 2] < array[index])
        {
            swap(array[index/2], array[index]);
            index /= 2;
        }
        else
        {
            return;
        }
    }
}

void ArrayHeap::percolate_down(int index) // index = 1
{
    while(index <= heap_index) // almost is while(true)
    {
        if(2 * index + 1 <= heap_index) // also < array.size().
        {
            // both children are in range
            if(array[index] > array[2 * index] && array[index] > array[2 * index + 1])
            {
                return;
            }
            else if(array[2 * index] > array[index] && array[2 * index] >= array[2 * index + 1])
            {
                swap(array[index], array[2 * index]);
                index = 2 * index;
            }
            else // right child is bigger
            {
                swap(array[index], array[2 * index + 1]);
                index = 2 * index + 1;
            }
        }
        else if (2 * index == heap_index)
        {
            // you are the very last node on the left and there's no right child
            if(array[2 * index] > array[index])
            {
                swap(array[index], array[2 * index]);
            }
            return;
        }
        else
        {
            return;
        }
    }
}

/*

    Why are all operations on an array based heap guaranteed to be O(lg(N))?
        peekMax = O(1)
        insert = O(lg(N))
        remove = O(lg(N))

        Why? Because a complete tree is pretty close to perfect, if you fill the last row, then it is perfect. 
        Add more nodes to the heap, it becomes a perfect tree. 
        What is the number of nodes in a perfect tree of height h?
            n = 2^{h + 1} - 1
            n + 1 = 2^{h + 1}
            lg(n + 1) = h + 1
            lg(n + 1) - 1 = h <-- number of total operations possible. 
            O(lg(n))
*/