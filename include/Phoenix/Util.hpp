#pragma once

#include "yaml-cpp/node/node.h"
#include <filesystem>
#include <string>

#include <yaml-cpp/yaml.h>

namespace phnx {
    std::string ReadTextFile(std::string filepath);

    YAML::Node LoadYAML(std::string filepath);
    void SaveYAML(std::string filepath, const YAML::Node& root);

    std::string ResourceDir();


}