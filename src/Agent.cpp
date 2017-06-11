//
// Created by tommy on 11.06.17.
//

#include "Agent.h"

void Agent::run() {

}

Agent::Agent(Configuration::SharedPtr configuration) {
    this->configuration = configuration;
}

void Agent::assignNewMorrons() {
    this->numberOfMoronsLeft = configuration->initialMoronsNumberPerAgent;
}
