#pragma once
#include "Entity.hpp"
#include "toml/value.hpp"
#include <cstdint>
#include <map>
#include <memory>
#include <random>
namespace  phnx {
    class Scene {
        public:
            std::shared_ptr<ecs::Entity> CreateEntity();
            void Serialize(toml::value& table);

            void Render();

        public:
            Scene();

        private:
            std::map<uint64_t, std::shared_ptr<ecs::Entity>> mEntities;
            std::default_random_engine mRNG;
            std::uniform_int_distribution<uint64_t> mDist;
            uint64_t NextID();
            
    };
}