//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_MESSAGE_H
#define UNEMPLOYED_MORRONS_MESSAGE_H

#include <cereal/types/polymorphic.hpp>
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

    static SharedPtr Create();

    virtual void foo() {}

protected:
    friend class cereal::access;
    Message() = default;

    template<class Archive>
    void serialize(Archive &ar) {
        ar(clock);
    }
};


#endif //UNEMPLOYED_MORRONS_MESSAGE_H
