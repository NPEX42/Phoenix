#pragma once

#include <entt/entt.hpp>

#include "ECS.hpp"

namespace phnx {
    namespace ecs {
        struct Entity {
            entt::entity ID = entt::null;

            template<typename T, typename ...Args>
            T& AddComponent(Args&& ...args) {
                return Registry().emplace<T>(ID, std::forward<Args>(args)...);
            }

            Entity();
            Entity(entity_t id);

            template<typename T>
            bool HasComponent() {
                return Registry().all_of<T>(ID);
            }

            template<typename T>
            T& GetComponent() {
                return Registry().get<T>(ID);
            }

            void Delete();
        };
        }
    }
