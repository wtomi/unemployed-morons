//
// Created by tommy on 11.06.17.
//

#include <iomanip>

#include "Agent.h"
#include "RequestCompanyMessage.h"
#include "ReplyCompanyMessage.h"

const int Agent::TAG = 0;
const int Agent::SETW = 6;

Agent::Agent(Configuration::SharedPtr configuration) {
    this->configuration = configuration;
    createCompanies();
}

void Agent::createCompanies() {
    auto companies = configuration->companies;
    for (int i = 0; i < companies.size(); i++) {
        auto company = companies[i];
        auto newCompany = Company::Create(i, company.maxMorons, company.maxDamageLevel, messenger.getSize());
        this->companies.push_back(newCompany);
    }
}

void Agent::run() {
    assignNewMorons(false);
    requestEntranceToEveryCompany(false);
    receiveAndHandleMessage();

    //TODO implemnt
}

void Agent::assignNewMorons(bool verbose) {
    this->numberOfMoronsLeft = configuration->initialMoronsNumberPerAgent;
    if (verbose)
        printAssingNewMorons(this->numberOfMoronsLeft);
}

void Agent::printAssingNewMorons(int numberOfAssignedMorons) {

}

void Agent::requestEntranceToEveryCompany(bool verbose) {
    for (auto &company: this->companies) {
        //any receiver can be passed as message is sent to all agents, -1 in this case
        auto requestMessage = RequestCompanyMessage::Create(-1, TAG, company->getCompanyId(),
                                                            this->numberOfMoronsLeft);
        auto message = std::dynamic_pointer_cast<Message>(requestMessage);
        messenger.sendToAll(message);
    }
    if (verbose)
        printRequestEntranceToEveryCompany();
}

void Agent::printRequestEntranceToEveryCompany() {
    printAgentInfoHeader();
    std::cout << "requests entrence to every company\n";
}

void Agent::receiveAndHandleMessage() {
    auto message = messenger.receiveFromAnySource(TAG);
    switch (message->type) {
        case Message::REQUEST_COMPANY:
            handleCompanyRequest(message);
            break;
        case Message::REPLY_COMPANY_REQUEST:
            handleReplyToCompanyRequest(message);
            break;
        default:
            break;
    }
    //TODO implement
}

void Agent::handleCompanyRequest(Message::SharedPtr &message, bool verbose) {
    auto requestMessage = std::dynamic_pointer_cast<RequestCompanyMessage>(message);
    int companyId = requestMessage->companyId;
    if (verbose)
        printHandleCompanyRequest(companyId);
    companies[companyId]->addRequest(requestMessage->rank, requestMessage->clock, requestMessage->requestedPlaces);
    //TODO implement
}

void Agent::printHandleCompanyRequest(int companyId) {
    printAgentInfoHeader();
    std::cout << "receives company request message | companyId: " << std::setw(SETW) << companyId << "\n";
}

void Agent::handleReplyToCompanyRequest(Message::SharedPtr &message, bool verbose) {
    auto replyMessage = std::dynamic_pointer_cast<ReplyCompanyMessage>(message);
    if (verbose)
        printHandleReplyToCompanyRequest(replyMessage->companyId);
    //TODO implement
}

void Agent::printHandleReplyToCompanyRequest(int companyId) {
    printAgentInfoHeader();
    std::cout << "receives reply to company request | companyId: " << std::setw(SETW) << companyId << "\n";
}

bool Agent::isMorronsLeft() {
    return numberOfMoronsLeft > 0;
}

void Agent::printAgentInfoHeader() {
    std::cout << "Clock: " << std::setw(SETW) << messenger.getClock()
              << " | rank: " << std::setw(SETW) << messenger.getRank() << " | ";
}
