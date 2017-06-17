//
// Created by tommy on 16.06.17.
//

#include <catch/catch.hpp>
#include "../src/Agent.h"

TEST_CASE("Test agent", "[agent]") {
    auto monitor = Monitor::getMonitor();
    Configuration::SharedPtr configuration;
    if (monitor->rank == 0) {
        configuration = Configuration::Create("testconfig.json");
        configuration->sendConfigurationToAllProceses();
    } else {
        configuration = Configuration::CreateFromReceivedMessage();
    }
    monitor->synchronize();
    Agent agent(configuration);
    agent.run();
}
