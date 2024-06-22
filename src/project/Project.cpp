#include "toml/parser.hpp"
#include "toml/value.hpp"
#include <Phoenix/project/Project.hpp>
#include <memory>
#include <string>

namespace phnx {
    std::shared_ptr<Project> LoadProject(std::string basedir) {
        toml::table config = toml::parse(basedir + "/config.toml").as_table();
        return std::make_shared<Project>(basedir, config);
    }



    Project::Project(const std::string& basedir, toml::table config) : mBaseDir(basedir), mConfig(config) {
        mAssetDir = basedir + "/assets";
        mScriptDir = basedir + "/scripts";
    }

}