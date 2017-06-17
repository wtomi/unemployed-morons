//
// Created by tommy on 11.06.17.
//

#include <iomanip>

#include "Agent.h"
#include "messages/RequestCompanyMessage.h"
#include "messages/ReplyCompanyMessage.h"
#include "messages/GoOutOfQueueMessage.h"
#include "messages/UpdateRequestMessage.h"

const int Agent::TAG = 0;
const int Agent::NW = 6;

Agent::Agent(Configuration::SharedPtr configuration) {
    this->configuration = configuration;
    createCompanies();
}

void Agent::createCompanies() {
    auto companies = configuration->companies;
    for (int i = 0; i < companies.size(); i++) {
        auto company = companies[i];
        auto newCompany = Company::Create(i, company.maxMorons, company.maxDamageLevel, messenger.getRank());
        this->companies.push_back(newCompany);
    }
}

void Agent::run() {
    bool freed = false;
    assignNewMorons();
    requestEntranceToEveryCompany();
    while (true) {
        receiveAndHandleMessage();
        if (numberOfMoronsLeft == 0 && !freed) {
            freeUnusedCompanies();
            updateRequests();
            freed = true;
        }
    }

    //TODO implemnt
}

void Agent::freeUnusedCompanies() {
    for (auto &company: companies) {
        if (company->getNumberOfMoronsPlaced() == 0) {
            auto request = company->getLastRequestOfCurrentAgent();
            sendGoOUtOfQueue(company->getCompanyId(), request->requestClock);
            company->removeLastRequestOfCurrentAgent();
        }
    }
}

void Agent::updateRequests() {
    for(auto &company: companies) {
        if(company->isChangedLastRequestOfCurrentAgent()) {
            auto request = company->getLastRequestOfCurrentAgent();
            sendUpdateRequest(company->getCompanyId(), request->requestClock, company->getNumberOfMoronsPlaced());
            company->updateLastRequestOfCurrentAgent();
        }
    }
}

void Agent::assignNewMorons(bool verbose) {
    this->numberOfMoronsLeft = configuration->initialMoronsNumberPerAgent;
    if (verbose)
        printAssingNewMorons(this->numberOfMoronsLeft);
}

void Agent::printAssingNewMorons(int numberOfAssignedMorons) {
    printAgentInfoHeader();
    std::cout << "takes new morons | numberOfMorons: " << std::setw(NW) << numberOfAssignedMorons << '\n';
}

void Agent::requestEntranceToEveryCompany(bool verbose) {
    for (auto &company: this->companies) {
        //any receiver can be passed as message is sent to all agents, -1 in this case
        Message::SharedPtr requestMessage = RequestCompanyMessage::Create(-1, TAG, company->getCompanyId(),
                                                                          this->numberOfMoronsLeft);
        messenger.sendToAll(requestMessage);

        company->addRequestOfCurrentAgent(messenger.getClock(), numberOfMoronsLeft);
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
        case Message::GO_OUT_OF_QUEUE:
            handleGoOutOfQueue(message);
            break;
        case Message::UPDATE_REQUEST:
            handleUpdateRequest(message);
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
        printHandleCompanyRequest(companyId, requestMessage->rank, requestMessage->clock);
    companies[companyId]->addRequest(requestMessage->rank, requestMessage->clock, requestMessage->requestedPlaces);
    sendReply(requestMessage->rank, companyId);
}

void Agent::handleReplyToCompanyRequest(Message::SharedPtr &message, bool verbose) {
    auto replyMessage = std::dynamic_pointer_cast<ReplyCompanyMessage>(message);
    if (verbose)
        printHandleReplyToCompanyRequest(replyMessage->companyId);
    auto company = companies[replyMessage->companyId];
    company->addReply();
    if (isMorronsLeft())
        tryToPlaceMoronsInCompany(company);
}

void Agent::handleGoOutOfQueue(Message::SharedPtr message, bool verbose) {
    auto goOutMessage = std::dynamic_pointer_cast<GoOutOfQueueMessage>(message);
    auto company = companies[goOutMessage->companyId];
    company->removeRequest(goOutMessage->rank, goOutMessage->requestClock);
    if (isMorronsLeft())
        tryToPlaceMoronsInCompany(company, verbose);
}

void Agent::handleUpdateRequest(Message::SharedPtr message, bool verbose) {
    auto updateRequestMessage = std::dynamic_pointer_cast<UpdateRequestMessage>(message);
    auto company = companies[updateRequestMessage->companyId];
    company->updateRequest(updateRequestMessage->rank, updateRequestMessage->requestClock,
                           updateRequestMessage->updatedRequestedPlaces);
    if(isMorronsLeft()) {
        tryToPlaceMoronsInCompany(company, verbose);
    }
}

void Agent::printHandleCompanyRequest(int companyId, int senderId, long senderClock) {
    printAgentInfoHeader();
    std::cout << "receives company request message | companyId: " << std::setw(NW) << companyId
              << " | senderId: " << std::setw(NW) << senderId
              << " | senderClock: " << std::setw(NW) << senderClock << '\n';
}

void Agent::sendReply(int receiverAgentId, int companyId, bool verbose) {
    Message::SharedPtr reply = ReplyCompanyMessage::Create(receiverAgentId, TAG, companyId);
    messenger.send(reply);
    if (verbose)
        printSendReply(receiverAgentId, companyId);
}

void Agent::printSendReply(int receiverAgentId, int comapnyId) {
    printAgentInfoHeader();
    std::cout << "sends reply to company request | receiverRank: " << std::setw(NW) << receiverAgentId
              << " | companyId: " << std::setw(NW) << comapnyId << '\n';
}

void Agent::printHandleReplyToCompanyRequest(int companyId) {
    printAgentInfoHeader();
    std::cout << "receives reply to company request | companyId: " << std::setw(NW) << companyId << '\n';
}

bool Agent::hasAllReplies(const Company::SharedPtr company, bool verbose) {
    assert(company->getNumberOfReplies() <= (messenger.getSize() - 1));
    bool hasAllReplies = company->getNumberOfReplies() == (messenger.getSize() - 1);
    if (verbose)
        printHasAllReplies(hasAllReplies);
    return hasAllReplies;
}

void Agent::printNoPlacesInCompany(int companyId) {
    printAgentInfoHeader();
    std::cout << "no places in | companyId: " << std::setw(NW) << companyId << '\n';
}

void Agent::printHasAllReplies(bool hasAllReplies) {
    printAgentInfoHeader();
    std::cout << "hasAllReplies: " << std::setw(NW) << hasAllReplies << '\n';
}

void Agent::tryToPlaceMoronsInCompany(Company::SharedPtr company, bool verbose) {
    if (hasAllReplies(company, verbose)) {
        int numberOfFreePlaces = company->getNumberOfFreePlacesForAgent(messenger.getRank());
        if (numberOfFreePlaces > 0) {
            placeMoronsInCompany(company, numberOfFreePlaces, verbose);
        } else {
            printNoPlacesInCompany(company->getCompanyId());
        }
    }
}

void Agent::placeMoronsInCompany(Company::SharedPtr company, int numberOfFreePlaces, bool verbose) {
    int numberOfTakenPlaces;
    if (numberOfFreePlaces >= numberOfMoronsLeft)
        numberOfTakenPlaces = numberOfMoronsLeft;
    else
        numberOfTakenPlaces = numberOfFreePlaces;
    company->placeMoronsInCompany(numberOfTakenPlaces);
    numberOfMoronsLeft -= numberOfTakenPlaces;
    if (verbose)
        printPlaceMoronsInCompany(company->getCompanyId(), numberOfTakenPlaces);
}

void Agent::printPlaceMoronsInCompany(int companyId, int numberOfTakenPlaces) {
    printAgentInfoHeader();
    std::cout << "places morons in company | companyId: " << std::setw(NW) << companyId
              << " | taken places: " << std::setw(NW) << numberOfTakenPlaces << '\n';
}

bool Agent::isMorronsLeft() {
    return numberOfMoronsLeft > 0;
}

void Agent::printAgentInfoHeader() {
    std::cout << "Clock: " << std::setw(NW) << messenger.getClock()
              << " | rank: " << std::setw(NW) << messenger.getRank() << " | ";
}

void Agent::sendGoOUtOfQueue(int companyId, long requestClock) {
    Message::SharedPtr message = GoOutOfQueueMessage::Create(-1, TAG, companyId, requestClock);
    messenger.sendToAll(message);
}

void Agent::sendUpdateRequest(int companyId, long requestClock, int moronsPlaced) {
    Message::SharedPtr message = UpdateRequestMessage::Create(-1, TAG, companyId, requestClock, moronsPlaced);
    messenger.sendToAll(message);
}
