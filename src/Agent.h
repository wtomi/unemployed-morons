//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_AGENT_H
#define UNEMPLOYED_MORRONS_AGENT_H


#include <mutex>
#include <thread>
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
    static const int NW;
    Configuration::SharedPtr configuration;
    Messenger messenger;
    std::vector<Company::SharedPtr> companies;
    int numberOfMoronsLeft;
    std::mutex mtx;
    std::thread t;

    void createCompanies();

    void assignNewMorons(bool verbose = true);

    void requestEntranceToEveryCompany(bool verbose = true);

    bool isMoronsLeft();

    void printAgentInfoHeader();

    void printRequestEntranceToEveryCompany();

    void handleCompanyRequest(Message::SharedPtr &message, bool verbose = true);

    void sendReply(int receiverAgentId, int companyId, long requestClock, bool verbose = true);

    void printSendReply(int receiverAgentId, int comapnyId);

    void handleReplyToCompanyRequest(Message::SharedPtr &message, bool verbose = true);

    bool hasAllReplies(const Company::SharedPtr, bool verbose = true);

    void tryToPlaceMoronsInCompany(Company::SharedPtr company, bool verbose = true);

    void receiveAndHandleMessage();

    void printHandleCompanyRequest(int companyId, int senderId, long senderClock);

    void printHandleReplyToCompanyRequest(int companyId);

    void printAssingNewMorons(int numberOfAssignedMorons);

    void placeMoronsInCompany(Company::SharedPtr company, int numberOfFreePlaces, bool verbose = true);

    void printPlaceMoronsInCompany(int companyId, int numberOfTakenPlaces);

    void printHasAllReplies(bool hasAllReplies);

    void printNoPlacesInCompany(int companyId);

    void sendGoOUtOfQueue(int companyId, long requestClock);

    void freeUnusedCompanies(bool verbose = true);

    void handleGoOutOfQueue(Message::SharedPtr message, bool verbose = true);

    void handleUpdateRequest(Message::SharedPtr message, bool verbose = true);

    void updateRequests(bool verbose = true);

    void sendUpdateRequest(int companyId, long requestClock, int moronsPlaced);

    void printFreeUnusedCompanies(int companyId, long requestClock);

    void printUpdateRequests(int companyId, long requestClock, int updatedRequestedPlaces);

    void breakCompany(Company::SharedPtr company, bool verbose = true);

    void sendBreakCompanyMessage(int companyId, int breakCount);

    void repairCompany(Company::SharedPtr company, bool verbose = true);

    void sendRepairCompanyMessage(int companyId, int repairCount);

    void handleBreakCompany(Message::SharedPtr message);

    bool wasAlreadyBroken(Company::SharedPtr company, int breakCount);

    void handleRepairCompany(Message::SharedPtr message);

    bool wasAlreadyRepaired(Company::SharedPtr company, int repairCount);

    void requestCompany(Company::SharedPtr &company);

    void monitorCompaniesDamage();

    void runMonitorCompaniesDamageThread();

    void resetLastRequestToAllCompanies();

    void monitorCompanies(std::vector<int> &companiesIterationsLeft);

    int computeWaitIterations() const;

    void monitorCompany(Company::SharedPtr &company, std::vector<int> &companiesIterationsLeft);

    void
    updateCompanyDamage(Company::SharedPtr &company, std::vector<int> &companiesIterationsLeft, int waitIterations);

    void tryToRepairCompany(Company::SharedPtr &company, std::vector<int> &companiesIterationsLeft);

    double computeDamageIncrease(Company::SharedPtr &company) const;

    void printBreakCompany(Company::SharedPtr company);

    void printRepairCompany(Company::SharedPtr company);

    bool ifCurrentAgentBroke(Company::SharedPtr &company, std::vector<int> &companiesIterationsLeft) const;
};


#endif //UNEMPLOYED_MORRONS_AGENT_H
