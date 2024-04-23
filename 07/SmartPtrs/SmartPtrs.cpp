#include <iostream>
#include <memory>
using namespace std;

class Test {
public:
    int Val;

    Test() : Val(0) {
        cout << "Constructor executed" << endl;
    }

    ~Test() {
        cout << "Destructor executed" << endl;
    }
};

shared_ptr<Test> foo() {
    shared_ptr<Test> ptr = make_shared<Test>();
    ptr->Val = 10;
    return ptr;
}

Test* goo() {
    Test* ptr = new Test();
    ptr->Val = 10;
    return ptr;
}

int main() {
    shared_ptr<Test> p1 = foo();
    cout << "Value of Val: " << p1->Val << endl;

    auto p2 = foo();
    cout << "Value of Val: " << p2->Val << endl;

    {
        auto p3 = foo();
        cout << "Value of Val: " << p3->Val << endl;
    }
    cout << "after block" << endl;

    shared_ptr<Test> t;
    {
        auto p4 = foo();
        t = p4;
        cout << "Value of Val: " << p4->Val << endl;
    }
    cout << "after block" << endl;
    return 0;
}
