#include <iostream>
#include <cstring>
#include "item.h"

using namespace std; 

Item::Item() {
}

char* Item::getName(){
  return name; 
}

int Item::getID(){
  return id; 
}

void Item::setName(char* inpName){
  name = inpName; 
}

void Item::setID(int inpID){
  id = inpID; 
}
