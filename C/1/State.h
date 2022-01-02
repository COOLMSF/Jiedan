/*
 * 3.Modify the State class to include a representation of a list of GameObjects
 * 7.Implement the player command get
 * 8.Implement the player command drop
 */
#ifndef TEXT_STATE_H
#define TEXT_STATE_H


#include "Room.h"
#include "GameObject.h"

class State {
private:
    Room *currentRoom;  //当前Room的指针
    list<GameObject*>inventory;

public:
    explicit State(Room *startRoom);//Constructor of the State class instance. Receives a pointer to an instance of Room class
    void goTo(Room *target);//The State class's function goTo(). Receives a pointer to an instance of Room class
    void announceLoc() const;
    Room* getCurrentRoom() const;//The usual function getCurrentRoom(). Returns a pointer to an instance of Room
    bool addObjectToInventory(string key);
    bool dropObjectFromInventory(string key);
    void showInventory();
};


#endif //TEXT_STATE_H
