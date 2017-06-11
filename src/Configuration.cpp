//
// Created by tommy on 11.06.17.
//

#include "Configuration.h"

Configuration::Configuration(std::string filepath) {
    std::ifstream inputStream(filepath);
    cereal::JSONInputArchive inputArchive(inputStream);
    inputArchive(*this);
}

Configuration::SharedPtr Configuration::Create(std::string filepath) {
    return Configuration::SharedPtr(new Configuration(filepath));
}
