#include <iostream>
#include "Monitor.h"

int main(int argc, char **argv) {

    Monitor monitor(&argc, &argv, nullptr);

    std::cout << "Hello, World!" << std::endl;

    return 0;
}