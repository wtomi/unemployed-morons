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

    static SharedPtr Create(int companyId, int maxNumberOfMorons, int maxDamegeLevel);

    int getCompanyId();

    void addRequest(int agentId, long agentClock, int requestedPlaces);

    void addReply();

    int getNumberOfReplies();

    int getNumberOfFreePlacesForAgent(int agentId);

    bool isRequestChanged(int agentId, int requestedPlaces);

    void updateRequest(int agentId, int numberOfRequestedPlaces);

    void placeMoronsInCompany(int numberOfMoronsPlaced);

    int getNumberOfMoronsPlaced();

private:
    Company(int companyId, int maxDamageLevel, int maxNumberOfMorons);

    int companyId;
    int maxNumberOfMorons;
    int maxDamageLevel;
    RequestsQueue requestsQueue;
    int numberOfReplies = 0;
    int numberOfMoronsPlaced = 0;
};


#endif //UNEMPLOYED_MORRONS_COMPANY_H
