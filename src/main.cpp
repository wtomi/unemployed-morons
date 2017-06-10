#include <iostream>
#include <cassert>
#include "Monitor.h"

void testMonitor(Monitor &monitor);

int main(int argc, char **argv) {

    Monitor monitor(&argc, &argv);

    testMonitor(monitor);

    return 0;
}

void testMonitor(Monitor &monitor) {
    const int tag = 0;
    std::string stringMessage("Hello!");
    std::stringstream stringStreamMessage(stringMessage);
    if(monitor.rank == 0) {
        for(int i = 1; i < monitor.size; i++) {
            monitor.send(stringStreamMessage, i, 0);
        }
    } else {
        std::stringstream receivedStringStreamMessage = monitor.receive();
        std::cout << receivedStringStreamMessage.str() << "\n";
        assert(receivedStringStreamMessage.str().compare(stringMessage) == 0);
    }
}