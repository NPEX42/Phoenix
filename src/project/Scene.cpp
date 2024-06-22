#include "Phoenix/AssetManager.hpp"
#include "Phoenix/gfx/Renderer2D.hpp"
#include "Phoenix/project/Component.hpp"
#include "Phoenix/project/ECS.hpp"
#include "Phoenix/project/Entity.hpp"
#include "toml/value.hpp"
#include <Phoenix/project/Scene.hpp>
#include <cstdint>
#include <memory>

namespace phnx {
    Scene::Scene() {
        mDist = std::uniform_int_distribution<uint64_t>(0, UINT64_MAX);
    }

    uint64_t Scene::NextID() {
        return mDist(mRNG);
    }

    std::shared_ptr<ecs::Entity> Scene::CreateEntity() {
        auto e = std::make_shared<ecs::Entity>();
        uint64_t uuid = NextID();
        e->AddComponent<ecs::Tag>("Empty Object", uuid);
        mEntities[uuid] = e;
        return e;
    }

    void Scene::Serialize(toml::value& table) {
        for (const auto& entry : mEntities) {
            auto ent = entry.second;
            if (ent->HasComponent<ecs::Tag>()) {
            SerializeComponent(table, ent->GetComponent<ecs::Tag>());
        }

        if (ent->HasComponent<ecs::Transform>()) {
            SerializeComponent(table, ent->GetComponent<ecs::Transform>());
        }

        if (ent->HasComponent<ecs::SpriteRenderer>()) {
            SerializeComponent(table, ent->GetComponent<ecs::SpriteRenderer>());
        }
        }

    }

    void Scene::Render() {
        for (auto entity : phnx::ecs::GetAllEntitiesWith<ecs::Transform, ecs::SpriteRenderer>()) {
            auto& t = phnx::ecs::GetComponent<ecs::Transform>(entity);
            auto& sr = phnx::ecs::GetComponent<ecs::SpriteRenderer>(entity);
            auto& tag = ecs::GetComponent<ecs::Tag>(entity);
            gfx::SetUUID(tag.UUID);
            phnx::gfx::SetAlbedo(phnx::AssetManager::GetTextureByName(sr.TextureID));
            phnx::gfx::RotatedQuad(t.Position, t.Rotation, t.Scale);
        }
        gfx::Flush();

    }

}