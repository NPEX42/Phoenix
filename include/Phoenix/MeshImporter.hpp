#pragma once

#include "Phoenix/Common.hpp"
#include "Phoenix/Mesh.hpp"
#include <string_view>
namespace phnx {
    Ref<Mesh> ImportFBX(const std::string& path);

}