//
// Created by tommy on 12.06.17.
//

#ifndef UNEMPLOYED_MORRONS_AGENTREQUEST_H
#define UNEMPLOYED_MORRONS_AGENTREQUEST_H


#include <memory>

class AgentRequest {
public:
    typedef std::shared_ptr<AgentRequest> SharedPtr;

    static SharedPtr Create(int agentId, long agentClock, int numberOdMorons);

    int agentId;

    long requestClock;
    int numberOfMorons;
private:
    AgentRequest(int agentId, long clock, int numberOfMorons);
};


#endif //UNEMPLOYED_MORRONS_AGENTREQUEST_H
