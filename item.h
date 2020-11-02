#ifndef item_h
#define item_h

#include <iostream>
#include <cstring>
#include <map>

using namespace std; 

class Item{
 public:
  Item(); 
  char* getName(); 
  int getID();
  void setName(char*);
  void setID(int);
 private: 
  char* name;
  int id;
}; 

#endif
