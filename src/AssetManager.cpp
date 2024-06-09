#include "Phoenix/Log.hpp"
#include "Phoenix/Util.hpp"
#include "Phoenix/gfx/Shader.hpp"
#include "Phoenix/gfx/Texture.hpp"
#include "Toml/Toml.hpp"
#include "yaml-cpp/node/node.h"
#include <Phoenix/AssetManager.hpp>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <glad/glad.h>
namespace phnx {
namespace AssetManager {

    static std::map<std::string, std::shared_ptr<gfx::Shader>> sShaders;
    static std::map<std::string, std::shared_ptr<gfx::Texture2D>> sTextures;

    static std::shared_ptr<gfx::Texture2D> sMISSING;

    std::map<std::string, std::shared_ptr<gfx::Texture2D>>& Textures() {
        return sTextures;
    }
    

    std::shared_ptr<gfx::Texture2D> GetTextureByName(std::string name) {
        if (sTextures.find(name) == sTextures.end()) {
            return sMISSING;
        }
        return sTextures[name];
    }

    void SetTextureByName(std::string name, std::shared_ptr<gfx::Texture2D> texture) {
        sTextures[name] = texture;
    }

    std::shared_ptr<gfx::Texture2D> LoadTexture2D(std::string name, std::string filepath, bool flip) {
        auto texture = gfx::LoadTexture2D(filepath, flip);
        sTextures[name] = texture;
        return texture;
    }

    std::shared_ptr<gfx::Shader> GetShaderByName(std::string name) {
        return sShaders[name];
    }

    std::shared_ptr<gfx::Shader> LoadShader(std::string name, std::string vertexPath, std::string fragmentPath) {
        auto vs_src = phnx::ReadTextFile(vertexPath);
        auto fs_src = phnx::ReadTextFile(fragmentPath);
        auto shader = std::make_shared<gfx::Shader>(vs_src, fs_src);
        sShaders[name] = shader;
        return shader;
    }

    void LoadTexturesFromTOML(std::string filepath) {
        toml::table assets = toml::parse_file(filepath);
        toml::table textures = *assets["Textures"].as_table();
        std::string resourceDir = *assets["ResourceDir"].value<std::string>();

        for (const auto& texture: textures) {
            std::string_view name = texture.first.str();
            std::string filename = *texture.second.value<std::string>();

            LoadTexture2D(std::string(name), resourceDir + "/" + filename, true);
        }

        uint32_t pixels[] = {0xFFFF00FF};
        sMISSING = gfx::CreateTexture2D(1, 1, pixels);
        sMISSING->SetFilterModes(GL_NEAREST, GL_NEAREST);
    }

    void ReloadTexturesFromTOML(std::string filepath) {
        for (const auto& entry : sTextures) {
            entry.second->Free();
        }

        LoadTexturesFromTOML(filepath);
    }

    void LoadShadersFromTOML(std::string filepath);
}
}
