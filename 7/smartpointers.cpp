#include <iostream>
#include <memory>

class Test {
public:
    Test() {
        std::cout << "Test constructed\n";
    }
    ~Test() {
        std::cout << "Test destructed\n";
    }
};

std::weak_ptr<Test> wp;

int main() {
    {
        auto sp = std::make_shared<Test>();
        std::cout << "use_count: " << sp.use_count() << std::endl;

        wp = sp;
        std::cout << "use_count after assigning to weak_ptr: " << sp.use_count() << std::endl;

        auto p = wp.lock();
        if (p) {
            std::cout << "object is alive, use_count: " << p.use_count() << std::endl;
        }
        else {
            std::cout << "no owning object\n";
        }
    }

    auto p = wp.lock();
    if (p) {
        std::cout << "object is alive, use_count: " << p.use_count() << std::endl;
    }
    else {
        std::cout << "no owning object\n";
    }

    return 0;
}
