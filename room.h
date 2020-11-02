#ifndef room_h
#define room_h

#include <iostream>
#include <cstring>
#include <map>

using namespace std;

class Room{
 public:
  Room(); 
  char* getDes();
  int getID(); 
  map<int, char*>* getExit(); 
  int getItem(); 
  void setDes(char*); 
  void setID(int); 
  void setExit(map<int, char*>); 
  void setItem(int); 
 private:
  char* des; 
  int id; 
  map <int, char*>exit; 
  int item; 
}; 
#endif
