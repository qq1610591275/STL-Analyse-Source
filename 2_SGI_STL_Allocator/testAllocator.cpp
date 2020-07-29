#include "testAllocator.h"
#include <vector>
#include <iostream>

#define __ALIGN 8

int round_up(int b) {
    return (((b) + __ALIGN - 1) & ~(__ALIGN - 1));
}

int main() {
    int ia[5] = {0, 1, 2, 3, 4};
    int i;

    std::vector<int, WG::allocator<int> > iv(ia, ia + 5);
    for (i = 0; i < iv.size(); i++) {
        std::cout << iv[i] << ' ';
    }
    std::cout <<std::endl;

    std::cout << ~(__ALIGN - 1) << std::endl;
    std::cout << round_up(3) << std::endl;
    std::cout << round_up(15) << std::endl;
}