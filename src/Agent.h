//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_AGENT_H
#define UNEMPLOYED_MORRONS_AGENT_H


#include "AgentInterface.h"
#include "Configuration.h"
#include "Company.h"
#include "Messenger.h"

class Agent : public AgentInterface {
public:
    Agent(Configuration::SharedPtr configuration);

    void run();

private:
    static const int TAG;
    Configuration::SharedPtr configuration;
    Messenger messenger;
    std::vector<Company::SharedPtr> companies;
    int numberOfMoronsLeft;

    void createCompanies();

    void assignNewMorons(bool verbose = true);

    void requestEntranceToEveryCompany(bool verbose = true);

    bool isMorronsLeft();

    void printAgentInfoHeader();

    void printRequestEntranceToEveryCompany();

    void handleCompanyRequest(Message::SharedPtr &message, bool verbose = true);

    void handleReplyToCompanyRequest(Message::SharedPtr &message, bool verbose = true);

    void receiveAndHandleMessage();

    void printHandleCompanyRequest(int companyId);

    void printHandleReplyToCompanyRequest(int companyId);

    void printAssingNewMorons(int numberOfAssignedMorons);
};


#endif //UNEMPLOYED_MORRONS_AGENT_H
