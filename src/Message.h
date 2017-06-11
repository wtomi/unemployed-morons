//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_MESSAGE_H
#define UNEMPLOYED_MORRONS_MESSAGE_H

#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>

class Message {
public:
    long clock;
    std::string word;

    template<class Archive>
    void serialize(Archive &ar) {
        ar(clock, word);
    }
};


#endif //UNEMPLOYED_MORRONS_MESSAGE_H
