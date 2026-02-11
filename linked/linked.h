/*
  You need two things:
  node structure (class, struct)
  Data structure itself (class, going to have functions).
  
 */
#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#define NOT_FOUND -1


struct Node
{
  int data;
  Node * p_next;
};


class LinkedList
{
 public:
  LinkedList();
  LinkedList(const LinkedList & copy_me);
  int search(int thing) const; // -1 means we didn't find it. 
  int get_at(int pos) const;
  void insert_at_head(int new_data);
  void insert_at_tail(int new_data);
  bool insert_at_pos(int new_data, int pos);
  bool remove_at_pos(int pos);
  bool remove_element(int data);
  LinkedList& operator=(const LinkedList & other_dude); 
  ~LinkedList();
 private:
  Node * p_head;
};

#endif 

