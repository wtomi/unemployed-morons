//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_AGENT_H
#define UNEMPLOYED_MORRONS_AGENT_H


#include "AgentInterface.h"
#include "Configuration.h"
#include "Company.h"
#include "Messenger.h"

class Agent: public AgentInterface {
public:
    Agent(Configuration::SharedPtr configuration);

    void run();

private:
    Configuration::SharedPtr configuration;
    Messenger messenger;
    std::vector<Company::SharedPtr> companies;
    int numberOfMoronsLeft;

    void createCompanies();
    void assignNewMorons();
    void requestEntrenceToEveryCompany();
    bool isMorronsLeft();
};


#endif //UNEMPLOYED_MORRONS_AGENT_H
