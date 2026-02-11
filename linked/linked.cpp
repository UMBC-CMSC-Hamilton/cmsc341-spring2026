/*
  You need two things:
  node structure (class, struct)
  Data structure itself (class, going to have functions).
  
 */
#include "linked.h"

/*
struct Node
{
  int data;
  Node * p_next;
};
*/

LinkedList::LinkedList()
  : p_head(nullptr)
{

}

LinkedList::LinkedList(const LinkedList & copy_me)
{
  /*
                
    copy_me: p_head->next->another->more->even_more
    
    us:      p_head->next->another->more->even_more

                   scan
    p_head->next->another
    
            current
    p_head->next
   */
  Node * scan = copy_me.p_head;
  if(scan)
  {
    p_head = new Node();
    p_head->data = scan->data;
    
    Node * current = p_head;
      
    scan = scan->p_next;
    while(scan)
    {
      current->p_next = new Node();
      current->p_next->data = scan->data;
      current = current->p_next;
      scan = scan->p_next;
    }
    current->p_next = nullptr;
  }
  else
  {
    p_head = nullptr;
  }
}


LinkedList& LinkedList::operator=(const LinkedList & other_dude)
{
  if(this == &other_dude)
  {
    return *this;
  }

  if (p_head)
  {
    this->~LinkedList();
  }
  
  Node * scan = other_dude.p_head;
  if (scan)
  {
    p_head = new Node();
    p_head->data = scan->data;
    
    Node * current = p_head;
    scan = scan->p_next;
    while(scan)
    {
      current->p_next = new Node();
      current->p_next->data = scan->data;
      current = current->p_next;
      scan = scan->p_next;
    }
    current->p_next = nullptr;
  }
  else
  {
    p_head = nullptr;
  }
  return *this;
}

int LinkedList::search(int thing) const // -1 means we didn't find it. 
/* searching for an element, not for an index */
{
  int index = 0;
  Node * current = p_head;
  while(current && current->data != thing)
  {
    current = current->p_next;
    index++;
  }
  if(current == nullptr)
  {
    return NOT_FOUND;
  }
  
  return index;
}

int LinkedList::get_at(int pos) const
{
  int index = 0;
  Node * current = p_head;

  if (pos < 0)
  {
    return 0; // bad -> throw exception, use optional, do anything but this. 
  }

  while(current && index < pos)
  {
    current = current->p_next;
    index++;
  }
  if(current == nullptr)
  {
    return 0; // throw an exception we'll get to it.
  }
  return current->data;
}

void LinkedList::insert_at_head(int new_data)
{
  /*
    two cases: 1) p_head doesn't exist (create it and put the data in)
               2) p_head does exist 
   */
  Node * p_new = new Node(); // this doesn't set anything, p_next is not set
  p_new->data = new_data;
  p_new->p_next = p_head;
  p_head = p_new; // reset what the linked list thinks the head pointer is.  
}

void LinkedList::insert_at_tail(int new_data)
{
  // we don't keep the tail pointer. p_tail but we don't have it.
  // you need to track to the end of the structure
  Node * current = p_head;
  if(!p_head)  // == nullptr
  {
    p_head = new Node();
    p_head->data = new_data;
    p_head->p_next = nullptr;
    return;
  }
  while(current->p_next)
  {
    current = current->p_next;
  }
  // current should be the end of the list and hopefully not null itself.
  current->p_next = new Node();
  current->p_next->data = new_data;
  current->p_next->p_next = nullptr; 
}

bool LinkedList::insert_at_pos(int new_data, int pos)
{
  //           pos
  // prev -> current -> next
  // prev -> new_one -> current -> next
  
  auto current = p_head;
  Node * previous = nullptr;

  if(pos < 0)
  {
    return false;
  }
  if(pos == 0)
  {
    insert_at_head(new_data);
    return true;
  }
  
  int current_position = 0;

  //for(int cur_pos = 0; current && cur_pos < pos; cur_pos++)
  while(current && current_position < pos)
  {
    previous = current;
    current = current->p_next;
    current_position++;
  }

  if(current == nullptr)
    return false;

  Node * new_node = new Node();
  new_node->data = new_data;
  new_node->p_next = current;
  previous->p_next = new_node;

  return true;
}

bool LinkedList::remove_at_pos(int pos)
{
  // prev -> pos_node -> next
  // prev -> next
  // pseudo_code: prev->p_next = next;

  if(pos < 0)
    return false;
  if(pos == 0)
  {
    // p_head -> maybe_next
    // p_head = maybe_next
    // delete the old p_head
    if(!p_head)
      return false;
    Node * old_node = p_head;
    p_head = p_head->p_next;
    delete old_node;
    return true;
  }

  int current_position = 0;
  Node * current = p_head;
  Node * previous = nullptr;

  while(current && current_position < pos)
  {
    current_position++;
    previous = current;
    current = current->p_next;
  }
  if (!current)
    return false;
  // this is the only line you actually care about, maybe the next one too...
  previous->p_next = current->p_next;
  delete current;
  return true;
}

bool LinkedList::remove_element(int data)
{
  Node * previous = nullptr;
  Node * current = p_head;

  if(!p_head)
  {
    return false;
  }
  else if(p_head && p_head->data == data)
  {
    Node * old_node = p_head;
    p_head = p_head ->p_next;
    delete old_node;
    return true;
  }

  for(; current && current->data != data; current= current->p_next)
  {
    previous = current;
  }
  if(!current)
    return false;

  previous->p_next = current->p_next;
  delete current;
  return true;
}

LinkedList::~LinkedList()
{
  Node * p_current = p_head;
  Node * temp;
  while(p_current)
  {
    temp = p_current;
    p_current = p_current->p_next;
    delete temp;
  }
}


