//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_CONFIGURATION_H
#define UNEMPLOYED_MORRONS_CONFIGURATION_H


#include <fstream>
#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"
#include "Monitor.h"
#include "Packet.h"

class Configuration {
public:
    typedef std::shared_ptr<Configuration> SharedPtr;
    static const int TAG;

    class Company {
    public:
        int maxDamageLevel;
        int maxMorons;

        template<class Archive>
        void serialize(Archive &archive) {
            archive(CEREAL_NVP(maxDamageLevel), CEREAL_NVP(maxMorons));
        }
    };

    static SharedPtr Create(std::string filepath);
    static SharedPtr CreateFromReceivedMessage();

    int initialMoronsNumberPerAgent;
    std::vector<Company> companies;
    unsigned int agentSleepTime;
    unsigned int companySleepTime;
    unsigned int threadUSleepTime;
    double damageFactor;

    void sendConfigurationToAllProceses();
private:
    friend class cereal::access;
    Configuration(std::istream &stream);

    template<class Archive>
    void serialize(Archive &archive) {
        archive(CEREAL_NVP(initialMoronsNumberPerAgent), CEREAL_NVP(companies),
        CEREAL_NVP(agentSleepTime), CEREAL_NVP(companySleepTime), CEREAL_NVP(threadUSleepTime),
        CEREAL_NVP(damageFactor));
    }

    void sendToAll(Monitor::SharedPtr monitor, Packet::SharedPtr packet);
};

#endif //UNEMPLOYED_MORRONS_CONFIGURATION_H
