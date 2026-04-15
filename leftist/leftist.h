#ifndef __LEFTIST_H__
#define __LEFTIST_H__


class Node
{
 public:
  Node(int new_pri=0)
    : priority(new_pri), npl(0), p_left(nullptr), p_right(nullptr)
    {}
  Node * p_left;
  Node * p_right;
  int priority;
  int npl;
};


class LeftistHeap
{
 public:
  LeftistHeap();
  void insert(int x);
  int getMin();
  int peekMin();
  void clear();
  void merge(LeftistHeap & lh);
  ~LeftistHeap();
 private:
  void clear_node(Node * p_kill);
  Node * merge(Node * a, Node * b);
  int calculate_npl(Node * node);
  Node * p_root;
};

#endif
