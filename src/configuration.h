#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include "../libs/yaml-cpp/include/yaml-cpp/yaml.h"
#include <string>

YAML::Node loadConfiguration(const std::string& filePath);
//extern YAML::Node loadConfiguration();

#endif // CONFIGURATION_H
