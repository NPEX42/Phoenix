
#include "Phoenix/Log.hpp"
#include "glad/glad.h"
#include <Phoenix/gfx/ogl/OGL.hpp>
#include <cstdint>
#include <string>
#include <sys/types.h>

#define GL_ERROR_STR_CASE(ec) case ec: PHNX_INFO("OpenGL Error 0x%04x: %s - %s", ec, #ec, call.c_str()); break;

namespace GL {
    void CheckError(const std::string& call) {
        int ec = glGetError();
        while (ec != GL_NO_ERROR) {
            switch (ec) {
                GL_ERROR_STR_CASE(GL_NO_ERROR)
                GL_ERROR_STR_CASE(GL_INVALID_ENUM)
                GL_ERROR_STR_CASE(GL_INVALID_FRAMEBUFFER_OPERATION)
                GL_ERROR_STR_CASE(GL_INVALID_OPERATION)
                GL_ERROR_STR_CASE(GL_OUT_OF_MEMORY)
                GL_ERROR_STR_CASE(GL_STACK_OVERFLOW)
                GL_ERROR_STR_CASE(GL_STACK_UNDERFLOW)
            }
            ec = glGetError();
        }
    }

    uint32_t DataTypeToGL(phnx::gfx::DataType type) {
        switch (type) {
            case phnx::gfx::F32: return GL_FLOAT;
            case phnx::gfx::F64: return GL_DOUBLE;
            case phnx::gfx::U8: return GL_UNSIGNED_BYTE;
            case phnx::gfx::U16: return GL_UNSIGNED_SHORT;
            case phnx::gfx::U32: return GL_UNSIGNED_INT;
            case phnx::gfx::U64: PHNX_DEBUG("MAX OPENGL DATATYPE: U32."); return GL_UNSIGNED_INT;
            case phnx::gfx::S8: return GL_BYTE;
            case phnx::gfx::S16: return GL_SHORT;
            case phnx::gfx::S32: return GL_INT;
            case phnx::gfx::S64: PHNX_DEBUG("MAX OPENGL DATATYPE: U32."); return GL_INT;
        }
        return GL_FLOAT;
    }
}