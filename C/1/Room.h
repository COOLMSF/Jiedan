#ifndef TEXT_ROOM_H
#define TEXT_ROOM_H

#include <string>
#include <forward_list>
#include <list>

#include "GameObject.h"


using namespace std;//Specify identifiers directly (global variables)


class Room {//Room 类
private:
    const string* name;  //房间的名称（字符串指针）
    const string* description;  //房间的描述
    Room* north;  //不同方向房间的指针
    Room* south;
    Room* west;
    Room* east;

public:
    list<GameObject*>objects;

public:
    Room(const string *_name, const string *_desc);  //Room的构造函数，先传入字符串名字和对应的指针

    ~Room();

    void describe() const;  //输出房间的名字

    static list<Room*> rooms;  //储存所有通过addRoom()添加的Room中的对象

    static Room* addRoom(const string* _name, const string* _desc);  //传入名称和字符串来添加Room到列表中
    static void addRoom(Room* room);  //传入Room的指针并添加到列表


    Room* getNorth() const;
    void setNorth(Room* _north);

    Room* getSouth() const;
    void setSouth(Room* _south);

    Room* getWest() const;
    void setWest(Room* _west);

    Room* getEast() const;
    void setEast(Room* _east);

    void addObjectToRoom(GameObject*obj);

};

#endif //TEXT_ROOM_H
