//player can navigate rooms, rooms have items and exits
//player can pick up items and drop them in rooms
//winning condition and way to quit
#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include "item.h"
#include "room.h"

using namespace std;

char input[15];

void initializeRooms(vector<Room*>* rooms);
void initializeItems(vector<Item*>* items);
void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom);
void printInventory(vector<Item*>* items, vector<int> inventory);
void pickItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inventory, int currentRoom, char name[]);
void dropItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inventory, int currentRoom, char name[]);
int move(vector<Room*>* rooms, int currentRoom, char direction[]);

int main(){
  vector<Room*> rooms;
  vector<Item*> items;
  vector<int> inventory;
  int currentRoom = 1;
  initializeItems(&items);
  initializeRooms(&rooms);
  cout << "Welcome to zuul, you can travel from room to room, as well as pick up and drop items." << endl << "Commands: help, quit, move, get, drop, inventory" << endl;
  while (true){
    cout << "You are in ";
    printRoom(&rooms, &items, currentRoom);
    cin >> input;
    cin.clear();
    cin.ignore(256, '\n');
    if (strcmp(input, "help") == 0){
      cout << endl << "Your objective is to find the exit. Type quit to end the game, move to move to another room, get to get an item, drop to drop an item, and inventory to see your items." << endl;
    }
    if (strcmp(input, "quit") == 0){
      cout << "Quitting..." << endl;
      break;
    }
    if (strcmp(input, "move") == 0){
      cout << endl << "Which direction would you like to move?(north, south, east, west)" << endl;
      cin >> input;
      cin.clear();
      cin.ignore(256, '\n');
      currentRoom = move(&rooms, currentRoom, input);
    }
    if (strcmp(input, "get") == 0){
      cout << endl << "What would you like to pick up?" << endl;
      cin.get(input, 15);
      cin.clear();
      cin.ignore(256, '\n');
      pickItem(&rooms, &items, &inventory, currentRoom, input);
    }
    if (strcmp(input, "drop") == 0){
      cout << endl << "What would you like to drop?" << endl << endl;
      cin.get(input, 15);
      cin.clear();
      cin.ignore(256, '\n');
      dropItem(&rooms, &items, &inventory, currentRoom, input);
    }
    if (strcmp(input, "inventory") == 0){
      cout << endl << "Inventory: " << endl;
      printInventory(&items, inventory);
    }
  }
  return 0;
}

void initializeRooms(vector<Room*>* rooms){
  char* west = (char*)("west");
  char* east = (char*)("east");
  char* north = (char*)("north");
  char* south = (char*)("south");
  map<int, char*> temp;

  Room* room = new Room();
  room -> setDes((char*)("the starting room"));
  room -> setID(1);
  temp.insert(pair<int, char*> (2, north));
  room -> setItem(0);
  room -> setExit(temp);
  rooms -> push_back(room);
  temp.clear();

  Room* closet = new Room();
  closet -> setDes((char*)("a dusty closet"));
  closet -> setID(2);
  temp.insert(pair<int, char*> (1, south));
  closet -> setItem(1);
  closet -> setExit(temp);
  rooms -> push_back(closet);
  temp.clear();
}

void initializeItems(vector<Item*>* items){
  Item* item = new Item();
  item -> setName((char*)("item"));
  item -> setID(1);
  items -> push_back(item);
}
void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom){
  vector<Room*>::iterator i;
  vector<Item*>::iterator j;
  for (i = rooms -> begin(); i != rooms -> end(); i++){
    if (currentRoom == (*i) -> getID()){
      cout << (*i) -> getDes() << "." << endl;
      cout << "Your exits are: ";
      for (map<int, char*>::const_iterator v = (*i) -> getExit() -> begin(); v != (*i) -> getExit() -> end(); v++){
	cout << v -> second << " ";
      }
      cout << endl;
      cout << "In this room there are: " << endl;
      for (j = items -> begin(); j != items -> end(); j++){
	if ((*i) -> getItem() == (*j) -> getID()){
	  cout << (*j) -> getName() << endl;
	}
      }
      cout << endl;
      break;
    }
  }
}

void printInventory(vector<Item*>* items, vector<int> inventory){
  vector<int>::iterator i;
  vector<Item*>::iterator j;
  for (i = inventory.begin(); i != inventory.end(); i++){
    for (j = items -> begin(); j != items -> end(); j++){
      if ((*i) == (*j) -> getID()){
	cout << (*j) -> getName() << endl;
      }
    }
  }
  cout << endl;
}

void pickItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inventory, int currentRoom, char name[]){
  vector<Room*>::iterator i;
  vector<Item*>::iterator j;
  for (i = rooms -> begin(); i != rooms -> end(); i++){
    if (currentRoom == (*i) -> getID()){
      for (j = items -> begin(); j != items -> end(); j++){
	if (((*i) -> getItem() == (*j) -> getID()) && (strcmp((*j) -> getName(), name) == 0)){
	  inventory -> push_back((*j) -> getID());
	  (*i) -> setItem(0);
	  cout << endl << "You have picked up " << (*j) -> getName() << endl;
	  return;
	}
      }
    }
  }
}

void dropItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inventory, int currentRoom, char name[]){
  vector<Room*>::iterator i;
  vector<Item*>::iterator j;
  vector<int>::iterator z;
  for (i = rooms -> begin(); i != rooms -> end(); i++){
    if (currentRoom == (*i) -> getID()){
      if ((*i) -> getItem() == 0){
	for (j = items -> begin(); j != items -> end(); j++){
	  if ((strcmp((*j) -> getName(), name) == 0)){
	    for(z = inventory -> begin(); z != inventory -> end(); z++){
	      if ((*z) == (*j) -> getID()){
		cout << endl << "You have dropped: " << (*j) -> getName() << endl << endl;
		(*i) -> setItem((*j) -> getID());
		z = inventory -> erase(z);
		return;
	      }
	    }
	  }
	}
      }
    }
  }
}

int move(vector<Room*>* rooms, int currentRoom, char direction[]){
  vector<Room*>::iterator i;
  for (i = rooms -> begin(); i != rooms -> end(); i++){
    if (currentRoom == (*i) -> getID()){
      map <int, char*> exit;
      exit = *(*i) -> getExit();
      map<int, char*>::const_iterator z;
      for(z = exit.begin(); z != exit.end(); z++){
	if (strcmp(z -> second, direction) == 0){
	  return z -> first;
	}
      }
    }
  }
  return 0;
}
