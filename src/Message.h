//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_MESSAGE_H
#define UNEMPLOYED_MORRONS_MESSAGE_H

#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/access.hpp>
#include <cereal/types/memory.hpp>

class Message {
public:
    typedef std::shared_ptr<Message> SharedPtr;

    int rank = -1;
    int tag = -1;

    long clock;
    std::string word;

    static SharedPtr Create();

    template<class Archive>
    void serialize(Archive &ar) {
        ar(clock, word);
    }
private:
    friend class cereal::access;

    Message() = default;
};


#endif //UNEMPLOYED_MORRONS_MESSAGE_H
