#include "glm/fwd.hpp"
#include "toml/value.hpp"
#include <Phoenix/project/Component.hpp>

namespace phnx {
    namespace ecs {

        template<>
        void SerializeComponent(toml::value &data, uint64_t &comp) {
            data["ID"] = comp;
        }

        template<>
        void SerializeComponent(toml::value &data, Tag &comp) {
            data["Tag"] = comp.Tag;
            data["UUID"] = comp.UUID;
        }

        template<>
        void SerializeComponent(toml::value &data, glm::vec2 &comp) {
            data.push_back(comp.x);
            data.push_back(comp.y);
        }

        template<>
        void SerializeComponent(toml::value &data, Transform &comp) {
            data["Transform"] = toml::value();
            data["Transform"]["Position"] = toml::array();
            data["Transform"]["Scale"] = toml::array();
            SerializeComponent(data["Transform"]["Position"], comp.Position);
            SerializeComponent(data["Transform"]["Scale"], comp.Scale);
            data["Transform"]["Rotation"] = comp.Rotation;
        }

        template<>
        void SerializeComponent(toml::value &data, SpriteRenderer &comp) {
            data["SpriteRenderer"] = {comp.TextureID};
        }

        

        
    }

}