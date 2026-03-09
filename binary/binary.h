#ifndef __BST_H__
#define __BST_H__

template<class T>
struct BinarySearchTreeNode
{
  BinarySearchTreeNode(T new_data = T())
  : p_left(nullptr), p_right(nullptr), data(new_data)
    {};
    BinarySearchTreeNode<T> * p_left;
    BinarySearchTreeNode<T> * p_right;
    T data;
};

template <class T>
class BinarySearchTree
{
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree & other_tree);
        void insert(T item);
        void remove(T item);
        bool find(T item) const;
        BinarySearchTreeNode<T> * find_node(T item);
        BinarySearchTreeNode<T> * find_parent(BinarySearchTreeNode<T> * find_me);
        BinarySearchTreeNode<T> * successor(BinarySearchTreeNode<T> * current);

        void display() const;
        void display_recursive(BinarySearchTreeNode<T> * current, int level = 0) const;
        void clear(BinarySearchTreeNode<T> * current);
        ~BinarySearchTree();
    private:
        BinarySearchTreeNode<T> * p_root;
};

//struct BinarySearchTreeNode<int>;
//class BinarySearchTree<int>;

#include"binary.cpp"
#endif
