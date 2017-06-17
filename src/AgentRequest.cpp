//
// Created by tommy on 12.06.17.
//

#include "AgentRequest.h"

AgentRequest::SharedPtr AgentRequest::Create(int agentId, long agentClock, int numberOdMorons) {
    return AgentRequest::SharedPtr(new AgentRequest(agentId, agentClock, numberOdMorons));
}

AgentRequest::AgentRequest(int agentId, long clock, int numberOfMorons)
        : agentId(agentId), requestClock(clock), numberOfMorons(numberOfMorons) {}
