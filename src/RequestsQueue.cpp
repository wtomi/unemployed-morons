//
// Created by tommy on 15.06.17.
//

#include "RequestsQueue.h"
#include <iostream>

void RequestsQueue::addRequest(AgentRequest::SharedPtr agentRequest) {
    RequestKey requestKey(agentRequest->agentId, agentRequest->requestClock);
    orderedRequests.insert(std::pair<RequestKey, AgentRequest::SharedPtr>(requestKey, agentRequest));
}

AgentRequest::SharedPtr RequestsQueue::getAgentRequest(int agentId, long agentClock) {
    return this->orderedRequests.at(RequestKey(agentId, agentClock));
}

void RequestsQueue::removeAgentRequest(int agentId, long agentClock) {
    orderedRequests.erase(RequestKey(agentId, agentClock));
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

void RequestsQueue::clear() {
    orderedRequests.clear();
}


