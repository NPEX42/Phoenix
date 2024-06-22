#pragma once
#include "glm/glm.hpp"
#include "toml/value.hpp"
#include <entt/entt.hpp>

namespace phnx {
    namespace ecs {
        template<typename T>
        void SerializeComponent(toml::value& data, T& comp);

        struct Transform {
            glm::vec2 Position;
            glm::vec2 Scale;
            float Rotation;
        };

        struct SpriteRenderer {
            std::string TextureID;
        };

        struct Tag {
            std::string Tag;
            uint64_t UUID;
        };
    }
}