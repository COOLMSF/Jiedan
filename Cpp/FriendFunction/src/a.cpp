#include <iostream>
using namespace std;

class X {
    friend class Y;

    private:
        int x;
        static int y;
    
    public:
        void Set(int i) {
            x = i;
        }

        void Display() {
            cout << "x="<<x<<",";
            cout << "y=" << y << endl;
        }
};

class Y {
    public:
        Y(int i, int j);
        void Display();
    private:
        X a;
};

int X::y = 1;
Y::Y(int i, int j) {
    a.x = i;
    X::y = j;
}

void Y::Display() {
    cout << "x=" << a.x << ",";
    cout << "y=" << X::y << endl;
}

int main() {
    X b;
    
    b.Set(5);
    b.Display();
    
    Y c(6,9);
    c.Display();
    b.Display();
}