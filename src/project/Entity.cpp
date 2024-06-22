#include "Phoenix/project/ECS.hpp"
#include <Phoenix/project/Entity.hpp>

namespace phnx {
    namespace ecs {
        Entity::Entity() {
            ID = CreateEntity();
        }

        Entity::Entity(entity_t id) {
            ID = id;
        }

        void Entity::Delete() {
            Registry().destroy(ID);
            ID = entt::null;
        }
    }

}