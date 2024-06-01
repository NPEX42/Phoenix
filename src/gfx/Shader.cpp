#include "glad/glad.h"
#include <cstdint>
#include <cstdio>
#include <gfx/Shader.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <strstream>

namespace phnx {
namespace gfx {
void Shader::Bind() { glUseProgram(mID); }

void Shader::Unbind() { glUseProgram(0); }

uint32_t Shader::GetUniformLocation(std::string name) {
    if (mUniforms.find(name) == mUniforms.end()) {
        uint32_t loc = 0;
        loc = glGetUniformLocation(mID, name.c_str());
        if (loc == -1)
            printf("Failed To Locate Uniform %s\n", name.c_str());

        mUniforms[name] = loc;
        return loc;
    }

    return mUniforms[name];
}

Shader::Shader(uint32_t ID) : mID(ID) {}

Shader::Shader(std::string vsSource, std::string fsSource) : mID(0) {
    uint32_t vs, fs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vsSource_cstr = vsSource.c_str();
    const char *fsSource_cstr = fsSource.c_str();

    glShaderSource(vs, 1, &vsSource_cstr, NULL);
    glShaderSource(fs, 1, &fsSource_cstr, NULL);

    glCompileShader(vs);
    glCompileShader(fs);

    GLint vertex_compiled;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &vertex_compiled);
    if (vertex_compiled != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(vs, 1024, &log_length, message);
        printf("Vertex Shader Compilation Failed:\n%s\n == SOURCE ==\n%s\n",
               message, vsSource_cstr);

        return;
    }

    GLint fragment_compiled;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &fragment_compiled);
    if (fragment_compiled != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(fs, 1024, &log_length, message);
        printf("Fragment Shader Compilation Failed:\n%s\n", message);
        return;
    }

    mID = glCreateProgram();

    glAttachShader(mID, vs);
    glAttachShader(mID, fs);

    glLinkProgram(mID);

    GLint program_linked;
    glGetProgramiv(mID, GL_LINK_STATUS, &program_linked);
    if (program_linked != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(mID, 1024, &log_length, message);
        printf("Program Linking Failed:\n%s\n", message);
        return;
    }
}

Shader *Shader::Load(std::string vsPath, std::string fsPath) {
    std::ifstream vs_file(vsPath);
    std::stringstream buffer;
    buffer << vs_file.rdbuf();

    std::string vsSrc = buffer.str();

    std::ifstream fs_file(fsPath);
    std::stringstream fs_buffer;
    fs_buffer << fs_file.rdbuf();

    std::string fsSrc = fs_buffer.str();

    return new Shader(vsSrc, fsSrc);
}

} // namespace gfx
} // namespace phnx
