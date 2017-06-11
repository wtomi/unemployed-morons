//
// Created by tommy on 11.06.17.
//

#ifndef UNEMPLOYED_MORRONS_CONFIGURATION_H
#define UNEMPLOYED_MORRONS_CONFIGURATION_H


#include <fstream>
#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"

class Configuration {
public:
    class Company {
    public:
        int maxDamageLevel;
        int maxMorons;

        template<class Archive>
        void serialize(Archive &archive) {
            archive(CEREAL_NVP(maxDamageLevel), CEREAL_NVP(maxMorons));
        }
    };

    Configuration(std::string filepath);

    int initialMoronsNumberPerAgent;
    std::vector<Company> companies;

    template<class Archive>
    void serialize(Archive &archive) {
        archive(CEREAL_NVP(initialMoronsNumberPerAgent), CEREAL_NVP(companies));
    }
};

#endif //UNEMPLOYED_MORRONS_CONFIGURATION_H
