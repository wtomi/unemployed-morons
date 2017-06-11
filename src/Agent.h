//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_AGENT_H
#define UNEMPLOYED_MORRONS_AGENT_H


#include "AgentInterface.h"
#include "Configuration.h"

class Agent: public AgentInterface {
public:
    Agent(Configuration::SharedPtr configuration);

    void run();

private:
    Configuration::SharedPtr configuration;
    int numberOfMoronsLeft;

    void assignNewMorrons();
};


#endif //UNEMPLOYED_MORRONS_AGENT_H
