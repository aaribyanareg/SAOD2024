#include <iostream>
#include <memory>
#include "Test.h"

std::weak_ptr<Test> wp;

int main() {
    {
        std::shared_ptr<Test> sp = std::make_shared<Test>();
        std::cout << "use_count: " << sp.use_count() << std::endl;

        wp = sp;
        std::cout << "use_count after assigning to weak_ptr: " << sp.use_count() << std::endl;

        auto p = wp.lock();
        if (p) {
            std::cout << "object is alive, use_count: " << p.use_count() << std::endl;
        }
        else {
            std::cout << "no owning object" << std::endl;
        }
    }

    auto p = wp.lock();
    if (p) {
        std::cout << "object is alive, use_count: " << p.use_count() << std::endl;
    }
    else {
        std::cout << "no owning object" << std::endl;
    }

    return 0;
}
