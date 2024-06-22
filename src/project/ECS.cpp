#include <Phoenix/project/ECS.hpp>

namespace phnx {
    namespace ecs {
        entt::registry sRegistry;
        entt::registry& Registry() {
            return sRegistry;
        }

        entity_t CreateEntity() {
            return sRegistry.create();
        }

        void DeleteEntity(entity_t id) {
            sRegistry.destroy(id);
        }
    }

}