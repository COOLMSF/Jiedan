/*
 * 3.Modify the State class to include a representation of a list
 * 7.Implement the player command get
 * 8.Implement the player command drop
 * 9.Implement the player command inventory
 */
#include "State.h"

void State::announceLoc() const {   //调用当前Room的描述函数来输出相关信息
    this->currentRoom->describe();
}

State::State(Room *startRoom) : currentRoom(startRoom) {};    //传入开始Room的指针赋值给当前房间

void State::goTo(Room *target) {  //移动时的函数，传入目标Room的指针
    this->currentRoom = target;  //移动的途径
    this->announceLoc();      //输出相应描述
}

Room* State::getCurrentRoom() const {     //get函数，返回当前Room的指针
    return this->currentRoom;
}

bool State::addObjectToInventory(string key) {  //用户输入一个key

    list<GameObject*>::const_iterator i;

    for (i = currentRoom->objects.begin(); i != currentRoom->objects.end(); i++) {  //遍历容器

        if((*((*i)->keyword)).compare(key)) {  //“const string* text”。return 1(no equal)

            continue;

        } else {  //return 0(both equal)

            list<GameObject*>::const_iterator it;

            for (it = this->inventory.begin(); it != this->inventory.end(); it++) {  //遍历容器

                if((*((*it)->keyword)).compare(key)) {

                    continue;

                } else {

                    return false;

                }

            }

            inventory.push_back(*i);  //通过push_back()函数将新元素加到容器最后。
            currentRoom->objects.remove(*i);

            return true;

        }

    }

    return false;

}

bool State::dropObjectFromInventory(string key) {

    list<GameObject*>::const_iterator i;

    for (i = this->inventory.begin(); i != this->inventory.end(); i++) {  //遍历容器

        if((*((*i)->keyword)).compare(key)) {

            continue;

        } else {

            currentRoom->addObjectToRoom(*i);  //drop进currentRoom
            inventory.remove(*i);
            return true;  //返回drop成功。

        }
    }

    return false;  //返回drop失败。

}

void State::showInventory() {

    list<GameObject*>::const_iterator i;

    for (i = this->inventory.begin(); i != this->inventory.end(); i++) {  //遍历容器
        wrapOut((*i)->name);  //该函数要求传入一个“const string* text”。
        wrapEndPara();
    }
}
