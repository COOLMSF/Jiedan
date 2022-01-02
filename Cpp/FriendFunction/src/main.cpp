// friend functions
#include <iostream>
using namespace std;

class Rectangle {
    int width, height;
  public:
    Rectangle() {}
    Rectangle (int x, int y) : width(x), height(y) {}
    int getArea() {return width * height;}

    friend Rectangle duplicate (const Rectangle&);
    static int saySomething();
};

int Rectangle::saySomething() {
    cout << "This is an rectangle";
}

Rectangle duplicate (const Rectangle& param) {
  Rectangle res;
  res.width = param.width*2;
  res.height = param.height*2;
  return res;
}

int main () {
  Rectangle foo;
  Rectangle bar (2,3);
  foo = duplicate (bar);
  cout << foo.getArea() << '\n';
  foo.saySomething();
  return 0;
}