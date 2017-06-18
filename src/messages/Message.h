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
    enum Type{
        REQUEST_COMPANY,
        REPLY_COMPANY_REQUEST,
        GO_OUT_OF_QUEUE,
        UPDATE_REQUEST,
        GO_TO_SLEEP,
        WAKE_UP,
        BREAK_COMPANY
    };

    int rank;
    int tag;

    int type;
    long clock;

    static SharedPtr Create(int rank, int tag, int type);

    virtual void foo() {}

protected:
    friend class cereal::access;
    Message(int rank, int tag, int type);
    Message() = default;

    template<class Archive>
    void serialize(Archive &ar) {
        ar(clock, type);
    }
};


#endif //UNEMPLOYED_MORRONS_MESSAGE_H
