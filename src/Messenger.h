//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_MESSANGER_H
#define UNEMPLOYED_MORRONS_MESSANGER_H


#include "Message.h"
#include "Monitor.h"

class Messenger {
public:
    void send(Message::SharedPtr &message);
    void sendToAll(Message::SharedPtr &message);
    Message::SharedPtr receive(int source, int tag);
    Message::SharedPtr receiveFromAnySource(int tag);
    Message::SharedPtr receiveFromAnySourceAnyTag();

    int getRank();
    int getSize();
    long getClock();
private:
    long clock = 0;
    Monitor::SharedPtr monitor = Monitor::getMonitor();

    void sendMessage(const Message::SharedPtr &message) const;
};


#endif //UNEMPLOYED_MORRONS_MESSANGER_H
