/*
 * 1. Create an GameObject class
 */

#ifndef TEXT_GAMEOBJECT_H  //防止一个源文件两次包含同一个头文件
#define TEXT_GAMEOBJECT_H  //宏（做定义），替换文本【TEXT】/常量定义
#include <list>
#include "wordwrap.h"  //文件包含

using namespace std;    //Specify identifiers directly (global variables)

class GameObject {  //create the GameObject class
public:
    const string* name, *long_desc, * keyword;  //Pointers in strings
    static list<GameObject*> objectSpace ;  //Setting static variables
    GameObject(const string* _name, const string* _desc, const string* _keyword);  //Type the pointer into the GameObject
    static bool showDesc(string keyword);   //Setting static variables
    static void addObjectToObjectSpace(GameObject* obj);   //Setting static variables

};


#endif


