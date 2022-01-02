/*
 * 2.Modify the Room class so that each Room includes a list of GameObjects
 * 3.Modify the Room::describe() method
 */
#include "Room.h"
#include "wordwrap.h"

list<Room*> Room::rooms;

Room::Room(const string* _name, const string *_desc) :  //构造Room的函数，传入有相应名称和描述的指针，初始情况下全部方向的设定都是空指针
        name(_name), description(_desc), north(nullptr),south(nullptr),west(nullptr),east(nullptr) {};



Room::~Room() {
    Room::rooms.remove(this);  //Room的析构函数（当前指针this传入remove并在容器中移除自身）
}


void Room::describe() const {  //描述Room的具体
    wrapOut(this->name); //调用wordwrap中的两个函数，输出名字和描述
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();

    list<GameObject*>::const_iterator i;
    for (i=this->objects.begin(); i!=this->objects.end();//Iterator iterates through the elements in the list "Objects" under the current room
    i++) {
        wrapOut((*i)->name);
        wrapEndPara();
    }
}


Room* Room::addRoom(const string* _name, const string *_desc) {  //在Room中做添加的函数
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);//add the new element in the back
    return newRoom;
}


void Room::addRoom(Room* room) {//静态函数addRoom（）
    Room::rooms.push_back(room);
}


Room* Room::getNorth() const {  //Room get...做Room返回的指针
    return this->north;
}
Room* Room::getSouth() const{
    return this->south;
}
Room* Room::getEast() const{
    return this->east;
}
Room* Room::getWest() const{
    return this->west;
}



void Room::setNorth(Room* _north) {  //Room set...传入和传递相应指针
    this->north = _north;
}
void Room::setSouth(Room* _south) {
    this->south = _south;
}
void Room::setWest(Room* _west) {
    this->west = _west;
}
void Room::setEast(Room* _east) {
    this->east = _east;
}

void Room::addObjectToRoom(GameObject *obj) {
    objects.push_back(obj);//add new element in the back
}