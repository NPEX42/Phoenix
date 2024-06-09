#pragma once
#include "gfx/Shader.hpp"
#include "gfx/Texture.hpp"
#include <map>
#include <memory>
#include <string>

namespace phnx {
namespace AssetManager {
    std::shared_ptr<gfx::Texture2D> GetTextureByName(std::string name);
    std::shared_ptr<gfx::Shader> GetShaderByName(std::string name);

    std::shared_ptr<gfx::Texture2D> LoadTexture2D(std::string name, std::string filepath, bool flip = false);
    void SetTextureByName(std::string name, std::shared_ptr<gfx::Texture2D> texture);
    std::shared_ptr<gfx::Shader> LoadShader(std::string name, std::string vertexPath, std::string fragmentPath);

    void LoadTexturesFromTOML(std::string filepath);
    void ReloadTexturesFromTOML(std::string filepath);
    void LoadShadersFromTOML(std::string filepath);


    std::map<std::string, std::shared_ptr<gfx::Texture2D>>& Textures();
}
}