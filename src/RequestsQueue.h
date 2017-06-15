//
// Created by tommy on 15.06.17.
//

#ifndef UNEMPLOYED_MORRONS_REQUESTSQUEUE_H
#define UNEMPLOYED_MORRONS_REQUESTSQUEUE_H


#include <map>
#include <unordered_map>
#include <cassert>
#include "AgentRequest.h"

class RequestsQueue {
public:
    void addRequest(AgentRequest::SharedPtr agentRequest);

    AgentRequest::SharedPtr getAgentRequest(int agentId);

    void romoveAgentRequest(int agentId);

    AgentRequest::SharedPtr getFirstRequest();

    AgentRequest::SharedPtr getNextRequest();

private:
    class RequestKey {
    public:
        typedef std::shared_ptr<RequestKey> SharedPtr;
        RequestKey(int agentId, long agentClock) {
            this->agentId = agentId;
            this->agentClock = agentClock;
        }

        long agentClock;
        int agentId;
    };

    class RequestKeyComparator {
    public:
        bool operator()(const RequestKey::SharedPtr &lhs, const RequestKey::SharedPtr &rhs) {
            if (lhs->agentClock < rhs->agentClock) return true;
            if (lhs->agentClock > rhs->agentClock) return false;
            if (lhs->agentId < rhs->agentId) return true;
            if (lhs->agentId > rhs->agentId) return false;
            assert(false);
        }
    };

    std::map<RequestKey::SharedPtr, AgentRequest::SharedPtr, RequestKeyComparator>::iterator orderedRequestsIterator;
    std::map<RequestKey::SharedPtr, AgentRequest::SharedPtr, RequestKeyComparator> orderedRequests;
    std::unordered_map<int, AgentRequest::SharedPtr> unorderedRequests;
};


#endif //UNEMPLOYED_MORRONS_REQUESTSQUEUE_H
