//
// Created by tommy on 11.06.17.
//

#include "Agent.h"
#include "RequestCompanyMessage.h"

Agent::Agent(Configuration::SharedPtr configuration) {
    this->configuration = configuration;
    createCompanies();
}

void Agent::createCompanies() {
    auto companies = configuration->companies;
    for(int i = 0; i < companies.size(); i++) {
        auto company = companies[i];
        auto newCompany = Company::Create(i, company.maxMorons, company.maxDamageLevel, messenger.getSize());
        this->companies.push_back(newCompany);
    }
}

void Agent::run() {
    assignNewMorons();

    //TODO implemnt
}

void Agent::assignNewMorons() {
    this->numberOfMoronsLeft = configuration->initialMoronsNumberPerAgent;
}

bool Agent::isMorronsLeft() {
    return numberOfMoronsLeft > 0;
}

void Agent::requestEntrenceToEveryCompany() {
    //TODO implment
}
