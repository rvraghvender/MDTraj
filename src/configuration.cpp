#include "configuration.h"


// This defines the configuration object and initializes it from a file.
YAML::Node loadConfiguration(const std::string& filePath) {
    static YAML::Node configuration = YAML::LoadFile(filePath);
    return configuration;
}

