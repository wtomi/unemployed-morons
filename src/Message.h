//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_MESSAGE_H
#define UNEMPLOYED_MORRONS_MESSAGE_H

#include <cereal/archives/binary.hpp>

class Message {
    long clock;
    char word[20];

    template<class Archive>
    void serialize(Archive &archive) {
        archive(clock, word);
    }
};


#endif //UNEMPLOYED_MORRONS_MESSAGE_H
