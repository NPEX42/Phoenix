#include <cstdint>
#include <glad/glad.h>
#include <Phoenix/Log.hpp>
#include <string>
#include <Phoenix/gfx/Api.hpp>
#ifdef DEBUG
#define GL_CHECK(call) do {call; GL::CheckError(#call);} while(false)
#else
#define GL_CHECK(call) do {call;} while(false)
#endif
namespace GL {
    void CheckError(const std::string& call);

    
    
    uint32_t DataTypeToGL(phnx::gfx::DataType type);
}