#pragma once
#include "toml/value.hpp"
#include <memory>
#include <string>
#include <toml.hpp>

namespace phnx {
    class Project {
        public:
            Project(const std::string& baseDir, toml::table config);
        public:
            const std::string& BaseDir() const {return mBaseDir;}
            const std::string& AssetDir() const {return mAssetDir;}
            const std::string& ScriptDir() const {return mScriptDir;}
        private:
            std::string mBaseDir, mScriptDir, mAssetDir;
            toml::table mConfig;
    };

    std::shared_ptr<Project> LoadProject(std::string basedir);
}