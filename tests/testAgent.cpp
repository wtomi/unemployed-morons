//
// Created by tommy on 16.06.17.
//

#include <catch/catch.hpp>
#include "../src/Agent.h"

TEST_CASE("Test agent", "[agent]") {
    auto configuration = Configuration::Create("testconfig.json");
    Agent agent(configuration);
    agent.run();
}
