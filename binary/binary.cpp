
#include<iostream>
#include "binary.h"

using namespace std;


template<typename T>
BinarySearchTree<T>::BinarySearchTree()
    : p_root(nullptr)
{
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree & other_tree)
{}

template<typename T>
void BinarySearchTree<T>::insert(T item)
{
    BinarySearchTreeNode<T> * current = p_root;
    if(!p_root)
    {
        p_root = new BinarySearchTreeNode<T>(item);
        return;
    }

    while(current)
    {
        if(item < current->data)
        {
            if(!current->p_left)
            {
                current->p_left = new BinarySearchTreeNode<T>(item);
                current = nullptr;
            }
            else
            {
                current = current->p_left;
            }
        }
        else
        {
            if(!current->p_right)
            {
                current->p_right = new BinarySearchTreeNode<T>(item);
                current = nullptr;
            }
            else
            {
                current = current->p_right;
            }
        }
    }
}
/*
                        1
                    3
                        4
            7        
                    8
                        
    10
                    11
            12
                        18
                    20
                        22



                        1
                    3
                        4
                    
                    
                        
    10
                    11
            12
                        18
                    20
                        22



    What if it's a leaf? Kill it.
    What if it's NOT a leaf? 
        Can we kill a leaf instead? And pretend.  --> Yes
        Either the  predecessor = greatest node less than "5" or the node we're deleting
                    successor = least node greater than (or equal to)  "5" or the node we're deleting.
                    either the successor is a leaf OR the succesor's succesor is a leaf or so on in that fashion

*/
template<typename T>
void BinarySearchTree<T>::remove(T item)
{
    BinarySearchTreeNode<T> * current = find_node(item); 
    BinarySearchTreeNode<T> * the_successor = successor(current);

    if(current && the_successor)
    {
      cout << "current: " << current->data << "\t" << "successor: " << the_successor->data << endl;
    }
    /*
        case where the current comes back, but there's no successor... what does that mean?
        either current is leaf (no children)
            delete it.
        or current only has a left child.
            do a little surgery, we can join the parent of the node to the left child delete the current... ehhhh
            write a find_parent function.
        
        if it has a successor then we exchange the data
            while loopy call delete on the succesor

    */
    // least node that is greater than the current node. left most node in the right subtree of the node.
    // check if the successor is leaf if yes, delete, if no, find the successor of that.  
    // probably some kind of while loop.
    
    if(current == p_root)
    {
      cout << "I'm the root" << endl;
        if(p_root->p_right)
        {
            the_successor = successor(p_root);
            p_root->data = the_successor->data;
            current = the_successor;
        }
        else if(p_root->p_left)
        {
	    auto new_root = p_root->p_left;
	    delete p_root;
            p_root = new_root;
            return;
        }
        else
        {
            delete p_root;
            p_root = nullptr;
        }
    }
    
    while(current)
    {
        if(current->p_right)
        {
            current->data = the_successor->data;
            current = the_successor;
            the_successor = successor(current);
	    if(current)
	      cout << "current: " << current->data << endl;
	    else if(current && the_successor)
	      cout << "current: " << current->data << "\t" << "successor: " << the_successor->data << endl;
        }
        else if (current->p_left) // it doesn't have a right child, doesn't have a successor, but we have a left subtree
        {
  	    cout << "only left" << endl;
            BinarySearchTreeNode<T> * parent = find_parent(current);
            if (parent->p_left == current)
            {
                parent->p_left = current->p_left;
                delete current;
                current = nullptr;
            }
            else
            {
                parent->p_right = current->p_left;
                delete current;
                current = nullptr;
            }
        }
        else // it's a leaf case... 
        {
	    cout << "only a leaf" << endl;
            BinarySearchTreeNode<T> * parent = find_parent(current);
	    cout << "parents value: " << parent->data << endl;
            if(parent->p_left == current)
            {
                parent->p_left = nullptr;
                delete current;
                current = nullptr;
            }
            else
            {
                parent->p_right = nullptr;
                delete current;
                current = nullptr;
            }
        }
    }
}

template<typename T>
BinarySearchTreeNode<T> * BinarySearchTree<T>::successor(BinarySearchTreeNode<T> * current)
{
    // successor is the least node that is GREATER than our current node.  What does that mean?
    // if it's greater then we go right. 
    if (!current)
    {
        return nullptr;
    }

    if(!current->p_right)
    {
        // if there's no right, then just return the left (even if it's null)
        return current->p_left;
    }

    current = current->p_right;
    while(current->p_left)
    {
        current = current->p_left;
    }
    return current;
}

template<typename T>
bool BinarySearchTree<T>::find(T item) const
{
    BinarySearchTreeNode<T> * current = p_root;
    while(current)
    {
        if(item < current->data)
        {
            current = current->p_left;
        }
        else if(item > current->data)
        {
            current = current->p_right;
        }
        else
        {
            return true; // we found it.  
        }
    }
    return false;
}



template<typename T>
BinarySearchTreeNode<T> * BinarySearchTree<T>::find_node(T item)
{
    BinarySearchTreeNode<T> * current = p_root;
    while(current)
    {
        if(item < current->data)
        {
            current = current->p_left;
        }
        else if(item > current->data)
        {
            current = current->p_right;
        }
        else
        {
            return current; // we found it.  
        }
    }
    return nullptr;
}


template<typename T>
BinarySearchTreeNode<T> * BinarySearchTree<T>::find_parent(BinarySearchTreeNode<T> * find_me)
{
    BinarySearchTreeNode<T> * current = p_root;
    if(p_root == find_me)
    {
        return nullptr; // the item was found but it's the root we'll have to do something special for that.  
    }

    while(current)
    {
        if(current->p_left && current->p_left == find_me)
	  return current;
	else if(current->p_right && current->p_right == find_me)
	  return current;
      
        if(find_me->data < current->data)
        {
            current = current->p_left;
        }
        else if(find_me->data >= current->data)
        {
            current = current->p_right;
        }
    }
    return nullptr;
}



/*
        head -> next -> another -> more -> stuff -> anotherthing -> yetmore -> etc -> nullptr

        Better to do recursively.  

                        left left
                left
                        left right
        root 
                        right left
                right
                        right right
*/
template<typename T>
void BinarySearchTree<T>::clear(BinarySearchTreeNode<T> * current)
{
    // smarter = call a recursive helper, set p_root = nullptr at the end of this function. 
    if(current)
    {
        clear(current->p_left);
        clear(current->p_right);
        delete current;
    }
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    clear(p_root);
    p_root = nullptr;
}

template<typename T>
void BinarySearchTree<T>::display() const
{
    display_recursive(p_root);
}

template<typename T>
void BinarySearchTree<T>::display_recursive(BinarySearchTreeNode<T> * current, int level) const
{
    if(!current)
        return;
    display_recursive(current->p_left, level + 1);
    for(int i = 0; i < level; i++)
        cout << "\t";
    cout << current->data << endl;
    display_recursive(current->p_right, level + 1);
}
