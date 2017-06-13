//
// Created by tommy on 12.06.17.
//

#ifndef UNEMPLOYED_MORRONS_COMPANY_H
#define UNEMPLOYED_MORRONS_COMPANY_H


#include <queue>
#include "AgentRequest.h"

class Company {
public:
    typedef std::shared_ptr<Company> SharedPtr;

    static SharedPtr Create(int companyId, int maxNumberOfMorons, int maxDamegeLevel, int numberOfAgents);

    int getCompanyId();

    void addRequest(int agentId, long agentClock, int requestedPlaces);

private:
    class Comparator {
        bool reverse;
    public:
        Comparator(const bool &revparam = false) { reverse = revparam; }

        bool operator()(const AgentRequest::SharedPtr &lhs, const AgentRequest::SharedPtr &rhs) const {
            if (reverse) return (lhs->clock > rhs->clock);
            else return (lhs->clock < rhs->clock);
        }
    };

    Company(int companyId, int maxDamageLevel, int maxNumberOfMorons);

    static int numberOfAgents;
    int companyId;
    int maxNumberOfMorons;
    int maxDamageLevel;

    std::priority_queue<AgentRequest::SharedPtr, std::vector<AgentRequest::SharedPtr>, Comparator> agentsRquestQueue;
    //TODO Correct initializing priority queue
    std::vector<AgentRequest::SharedPtr> agentsRequests;
};


#endif //UNEMPLOYED_MORRONS_COMPANY_H
