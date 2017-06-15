//
// Created by tommy on 12.06.17.
//

#ifndef UNEMPLOYED_MORRONS_COMPANY_H
#define UNEMPLOYED_MORRONS_COMPANY_H


#include "AgentRequest.h"
#include "RequestsQueue.h"

class Company {
public:
    typedef std::shared_ptr<Company> SharedPtr;

    static SharedPtr Create(int companyId, int maxNumberOfMorons, int maxDamegeLevel, int numberOfAgents);

    int getCompanyId();

    void addRequest(int agentId, long agentClock, int requestedPlaces);

private:
    Company(int companyId, int maxDamageLevel, int maxNumberOfMorons);

    static int numberOfAgents;
    int companyId;
    int maxNumberOfMorons;
    int maxDamageLevel;
    RequestsQueue requestsQueue;
};


#endif //UNEMPLOYED_MORRONS_COMPANY_H
