//
// Created by tommy on 18.06.17.
//

#include "RepairCompanyMessage.h"

RepairCompanyMessage::SharedPtr RepairCompanyMessage::Create(int rank, int tag, int companyId, int repairCount) {
    return RepairCompanyMessage::SharedPtr(new RepairCompanyMessage(rank, tag, companyId, repairCount));
}

RepairCompanyMessage::RepairCompanyMessage(int rank, int tag, int companyId, int repairCount):
Message(rank, tag, Message::Type::REPAIR_COMPANY), companyId(companyId), repairCount(repairCount){
}

