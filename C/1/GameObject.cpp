/*
 * 1.The Object class contain a short name, a long description, and a keyword
 * 10. When typed with an object keyword, will print out the long description of that object.
 */
#include "GameObject.h"

list<GameObject*> GameObject::objectSpace; //Global variables
GameObject::GameObject(const string *_name, const string *_desc, const string *_keyword): name(_name), long_desc(_desc), keyword(_keyword){};

bool GameObject::showDesc(string key) {  //The functions to show long_describe
    list<GameObject*>::const_iterator i;  //Forward iterator(容器类名::const_iterator 迭代器名)
    for (i = GameObject::objectSpace.begin(); i !=GameObject::objectSpace.end(); i++) {  //Set up start and end conditions(遍历容器)
        if ((*((*i)->keyword)).compare(key)){ //Extract the keyword in *1 firstly,to compare with key, and return 1 if they are not equal
            continue;
        } else{ //Return 0 if both are equal
            wrapOut((*i)->long_desc); //Pass the value of * I to long_desc
            wrapEndPara();
            return true;

        }

    }
    return false;
}

void GameObject::addObjectToObjectSpace(GameObject *obj) {
    GameObject::objectSpace.push_back(obj); //Use push_back to add
}