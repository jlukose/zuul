#include <iostream>
#include <cstring>
#include "room.h"

using namespace std; 

Room::Room(){
}

char* Room::getDes(){ 
  return des; 
}

int Room::getID(){
  return id; 
}

map<int, char*>* Room::getExit(){
  return &exit; 
}

int Room::getItem(){
  return item; 
}

void Room::setDes(char* inpDes){
  des = inpDes; 
}

void Room::setID(int inpID){
  id = inpID; 
}

void Room::setExit(map<int, char*> inpExit){
  exit = inpExit; 
}

void Room::setItem(int inpItem){
  item = inpItem; 
}
