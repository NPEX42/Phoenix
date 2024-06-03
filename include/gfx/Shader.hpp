#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
namespace phnx {
namespace gfx {
class Shader {
public:
    void Bind();
    void Unbind();

    Shader(uint32_t ID);
    Shader(std::string vsSource, std::string fsSource);
    static Shader *Load(std::string vsPath, std::string fsPath);

public:
    void SetInt(std::string name, int value);

private:
    uint32_t mID;
    std::unordered_map<std::string, uint32_t> mUniforms;

    uint32_t GetUniformLocation(std::string name);
};
} // namespace gfx
} // namespace phnx
