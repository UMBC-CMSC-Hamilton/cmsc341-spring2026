#include<string>
#include "hash.h"

#define STARTING_CAPACITY 10

HashTable::HashTable()
  : size(0), capacity(STARTING_CAPACITY)
{
  // unassigned is an empty string. 
  array = new string[capacity];
}

void HashTable::insert(string s)
{
  int hash_val = hash(s) % capacity;
  int probe = 0;
  while(array[(hash_val + probe) % capacity] != "" && probe < capacity)
  {
    probe++;
  }
  array[(hash_val + probe) % capacity] = s;
  // maybe if you go all the way around throw an exception (tell the programmer-user that something happened)
  // the table is full and no one is helping to rehash.  
}

bool HashTable::find(string s)
{
  int hash_val = hash(s) % capacity;
  int probe = 0;
  while(array[(hash_val + probe) % capacity] != s && array[(hash_val + probe) % capacity] != "" && probe < capacity)
  {
    probe++;
  }
  return array[(hash_val + probe) % capacity] == s;
}

double HashTable::load_factor() const
{
  // we're safe because i'm never going to allow capacity to be less than 10. 
  return double(size)/capacity;
}

HashTable::~HashTable()
{
  delete [] array;
}

int HashTable::hash(string s)
{
  int prime = 17;
  int prime_power = 1;
  int hash_val = 0;
  for(int i = 0; i < s.length(); i++)
  {
    hash_val += int(s[i]) * prime_power;
    prime_power *= prime;
  }
  return hash_val;
}

void HashTable::rebuild(int new_size)
{
  // pick actual new capacity to be a prime larger than the new_size
  n = new_size;
  while(!is_prime(n))
  {
    n++;
  }
  // new_capacity = n
  string * new_array = new string[n];
  string * temp = array;
  array = new_array;
  int old_capacity = capacity;
  capacity = n;
  size = 0;
  for(int i = 0; i < old_capacity; i++)
  {
    if(temp[i] != "")
      insert(temp[i]);
  }
  delete [] temp;
}

bool HashTable::is_prime(int n)
{
  // O(sqrt(n))
  for(int i = 2; i * i <= n; i++)
  {
    if(n % i == 0)
      return false;
  }
  return true;
}

/*
string * array;
int capacity; // the size of the array (L)
int size; // the number of elements (n)
*/

#endif
