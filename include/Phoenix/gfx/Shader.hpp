#pragma once

#include <cstdint>
#include <memory>
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

class ComputeShader {
public:
    void Bind();
    void Unbind();

    ComputeShader(uint32_t ID);
    ComputeShader(std::string source);
    static std::shared_ptr<ComputeShader> Load(std::string filepath);

public:
    void SetInt(std::string name, int value);
    void SetFloat(std::string name, float value);
    void SetFloat2(std::string name, float x, float y);

    void DispatchSync(int x, int y = 1, int z = 1);
    void Dispatch(int x, int y = 1, int z = 1);

private:
    uint32_t mID;
    std::unordered_map<std::string, uint32_t> mUniforms;

    uint32_t GetUniformLocation(std::string name);
};
} // namespace gfx
} // namespace phnx
