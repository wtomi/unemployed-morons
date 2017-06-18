//
// Created by tommy on 18.06.17.
//

#ifndef UNEMPLOYED_MORRONS_REPAIRCOMPANYMESSAGE_H
#define UNEMPLOYED_MORRONS_REPAIRCOMPANYMESSAGE_H


#include "Message.h"

class RepairCompanyMessage : public Message {
public:
    typedef std::shared_ptr<RepairCompanyMessage> SharedPtr;

    int companyId;
    int repairCount;

    static SharedPtr Create(int rank, int tag, int companyId, int repairCount);

private:
    friend class cereal::access;

    RepairCompanyMessage() : Message() {}

    RepairCompanyMessage(int rank, int tag, int companyId, int repairCount);

    template<class Archive>
    void serialize(Archive &ar) {
        ar(cereal::base_class<Message>(this), companyId, repairCount);
    }
};

CEREAL_REGISTER_TYPE(RepairCompanyMessage);

#endif //UNEMPLOYED_MORRONS_REPAIRCOMPANYMESSAGE_H
