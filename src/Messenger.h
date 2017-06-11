//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_MESSANGER_H
#define UNEMPLOYED_MORRONS_MESSANGER_H


#include "Message.h"
#include "Monitor.h"

class Messenger {
public:
    void send(Message::SharedPtr message);
    Message::SharedPtr receive(int source, int tag);
    Message::SharedPtr receive();

    int getRank();
    int getSize();
private:
    Monitor monitor;
};


#endif //UNEMPLOYED_MORRONS_MESSANGER_H
