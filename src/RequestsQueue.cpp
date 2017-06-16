//
// Created by tommy on 15.06.17.
//

#include "RequestsQueue.h"
#include <iostream>

void RequestsQueue::addRequest(AgentRequest::SharedPtr agentRequest) {
    RequestKey requestKey(agentRequest->agentId, agentRequest->clock);
    orderedRequests.insert(std::pair<RequestKey, AgentRequest::SharedPtr>(requestKey, agentRequest));
    unorderedRequests.insert(std::pair<int, AgentRequest::SharedPtr>(agentRequest->agentId, agentRequest));
}

AgentRequest::SharedPtr RequestsQueue::getAgentRequest(int agentId) {
    return this->unorderedRequests.at(agentId);
}

void RequestsQueue::removeAgentRequest(int agentId) {
    auto &request = unorderedRequests.at(agentId);
    unorderedRequests.erase(agentId);
    RequestKey key(agentId, request->clock);
    orderedRequests.erase(key);
}

AgentRequest::SharedPtr RequestsQueue::getFirstRequest() {
    orderedRequestsIterator = orderedRequests.begin();
    if (orderedRequestsIterator != orderedRequests.end())
        return orderedRequestsIterator->second;
    else
        return nullptr;
}

AgentRequest::SharedPtr RequestsQueue::getNextRequest() {
    if (++orderedRequestsIterator != orderedRequests.end())
        return orderedRequestsIterator->second;
    else
        return nullptr;
}


