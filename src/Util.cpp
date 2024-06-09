#include "yaml-cpp/node/parse.h"
#include <Phoenix/Util.hpp>
#include <fstream>
#include <sstream>
#include <string>
namespace phnx {
    std::string ReadTextFile(std::string filepath) {
        std::ifstream stream(filepath);
        std::stringstream buffer;
        buffer << stream.rdbuf();

        stream.close();
        return buffer.str();
    }

    YAML::Node LoadYAML(std::string filepath) {
        return YAML::LoadFile(filepath);
    }

    void SaveYAML(std::string filepath, const YAML::Node& root) {
        std::ofstream fout(filepath);
        fout << root;
        fout.close();
    }

}