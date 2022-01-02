/*
 *5.Modify the gameLoop method to pay attention to the second word
 *6.Modify the gameLoop command to search through a) objects in the current room
 * 7.Implement the player command get
 * 8.Implement the player command drop
 * 9.Implement the player command inventory
 * 10.Implement the player command examine
 */
#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>

#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"

using namespace std;

string commandBuffer;//The global variable(commandBuffer)
State *currentState;//The global variable(*currentState)


void inputCommand(string *buffer) {
    buffer->clear();
    cout << "> ";
    getline(cin, *buffer);
}


void initRooms() {   //设置最初始化的房间
    auto * r5 = new Room(&r5name, &r5desc);
    auto * r4 = new Room(&r4name, &r4desc);
    auto * r3 = new Room(&r3name, &r3desc);
    auto * r2 = new Room(&r2name, &r2desc);
    auto * r1 = new Room(&r1name, &r1desc);

    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);

    r1->setNorth(r2);
    r2->setSouth(r1);
    r1->setEast(r3);
    r3->setWest(r1);
    r1->setSouth(r4);
    r4->setNorth(r1);
    r1->setWest(r5);
    r5->setEast(r1);

    auto* obj_knife = new GameObject(&obj_knife_name,&obj_knife_desc,&obj_knife_key);
    auto* obj_apple = new GameObject(&obj_apple_name,&obj_apple_desc,&obj_apple_key);
    auto* obj_phone = new GameObject(&obj_phone_name,&obj_phone_desc,&obj_phone_key);
    auto* obj_cup = new GameObject(&obj_cup_name,&obj_cup_desc,&obj_cup_key);

    GameObject::addObjectToObjectSpace(obj_apple);
    GameObject::addObjectToObjectSpace(obj_knife);
    GameObject::addObjectToObjectSpace(obj_cup);
    GameObject::addObjectToObjectSpace(obj_phone);

    r2->addObjectToRoom(obj_knife);
    r3->addObjectToRoom(obj_cup);
    r4->addObjectToRoom(obj_apple);
    r5->addObjectToRoom(obj_phone);
}



void initState() {  //初始化当前状态
    currentState = new State(Room::rooms.front());
    //Return variable of the Room class, passing in State with a reference to an element in Room as an argument
}


void gameLoop() {  //主循环程序
    bool gameOver=false;    //游戏结束时的状态
    while (!gameOver) {   //运用while语句来判断游戏是否结束
        bool commandOk = false;     //命令的状态（错误）
        inputCommand(&commandBuffer);   //输入命令


        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));//Get the position where the space appears to determine the end of the action
        if (unsigned(endOfVerb) != 255) {//输入“双指令”（用户的输入字符串出现了空格）
            string command = commandBuffer.substr(0, endOfVerb);//Get the "command" string
            string keyword = commandBuffer.substr(endOfVerb + 1, commandBuffer.length() - endOfVerb - 1);//get the "keyword" string

            if (!command.compare("get")) {
                if (currentState->addObjectToInventory(keyword)) {
                    cout << "get successfully" << endl;
                } else {
                    cout << "get unsuccessfully" << endl;
                }
            }

            if (!command.compare("drop")) {
                if (currentState->dropObjectFromInventory(keyword)) {
                    cout << "drop successfully" << endl;
                } else {
                    cout << "drop unsuccessfully" << endl;
                }
            }

            if (!command.compare("examine")) {
                if (GameObject::showDesc(keyword)) {
                    cout << "examine successfully" << endl;
                } else {
                    cout << "examine unsuccessfully" << endl;
                }
            }
        } else { //单指令（用户输入无空格时）

            if ((commandBuffer.compare(0, endOfVerb, "north") == 0) ||(commandBuffer.compare(0, endOfVerb, "n") == 0)) {
                commandOk = true;   //命令的状态（正确）
                Room *northRoom = currentState->getCurrentRoom()->getNorth();  //命令的路径表达
                if (northRoom == nullptr) {    //当空指针时对应的否定状态文本
                    wrapOut(&badExit);
                    wrapEndPara();
                } else {     //输出设定的语言描述
                    currentState->goTo(northRoom);
                }
            }

            if ((commandBuffer.compare(0, endOfVerb, "south") == 0) ||(commandBuffer.compare(0, endOfVerb, "s") == 0)) {
                commandOk = true;
                Room *southRoom = currentState->getCurrentRoom()->getSouth();
                if (southRoom == nullptr) {
                    wrapOut(&badExit);
                    wrapEndPara();
                } else {
                    currentState->goTo(southRoom);
                }
            }

            if ((commandBuffer.compare(0, endOfVerb, "west") == 0) || (commandBuffer.compare(0, endOfVerb, "w") == 0)) {
                commandOk = true;
                Room *westRoom = currentState->getCurrentRoom()->getWest();
                if (westRoom == nullptr) {
                    wrapOut(&badExit);
                    wrapEndPara();
                } else {
                    currentState->goTo(westRoom);
                }
            }

            if ((commandBuffer.compare(0, endOfVerb, "east") == 0) || (commandBuffer.compare(0, endOfVerb, "e") == 0)) {
                commandOk = true;
                Room *eastRoom = currentState->getCurrentRoom()->getEast();
                if (eastRoom == nullptr) {
                    wrapOut(&badExit);
                    wrapEndPara();
                } else {
                    currentState->goTo(eastRoom);
                }
            }

            if (commandBuffer.compare(0, endOfVerb, "inventory") == 0) {
                commandOk = true;
                currentState->showInventory();
            }

            if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) { //state of game over
                commandOk = true;
                gameOver = true;
            }


            if (!commandOk) { //When the verb is invalid, negative text is printed
                wrapOut(&badCommand);
                wrapEndPara();
            }
        }
    }
}






int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}