//
// Created by tommy on 12.06.17.
//

#ifndef UNEMPLOYED_MORRONS_AGENTREQUEST_H
#define UNEMPLOYED_MORRONS_AGENTREQUEST_H


#include <memory>

class AgentRequest {
public:
    typedef std::shared_ptr<AgentRequest> SharedPtr;
    static SharedPtr Create();

    long clock;
    int numberOfMorons;
private:
    AgentRequest() = default;
};


#endif //UNEMPLOYED_MORRONS_AGENTREQUEST_H
