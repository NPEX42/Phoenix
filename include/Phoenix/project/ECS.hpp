#pragma once
#include <entt/entt.hpp>
#include <utility>

typedef entt::entity entity_t;

namespace phnx {
    namespace ecs {
        entt::registry& Registry();
        entity_t CreateEntity();
        void DeleteEntity(entity_t id);

        template<typename T, typename ...Args>
        T& AddComponent(entity_t entity, Args&& ...args) {
            return Registry().emplace<T>(entity, std::forward<Args>(args)...);
        }


        template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return Registry().view<Components...>();
		}

        template<typename T>
        T& GetComponent(entity_t e) {
           return Registry().get<T>(e);
        }
    }
}