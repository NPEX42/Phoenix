#pragma once

#include "Phoenix/gfx/Texture.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_int2.hpp"
#include <map>
#include <memory>
namespace phnx {
    namespace gfx {

        struct Rect {
            int X, Y, Width, Height;
        };

        struct RectUVs {
            glm::vec2 UV0, UV1;
        };

        class TextureAtlas {
        public:
            TextureAtlas(std::shared_ptr<Texture2D> texture) : mTexture(texture) {}
            glm::vec2 GetUV(const glm::ivec2& point); 

            

            std::shared_ptr<Texture2D> const Texture() const { return mTexture; }
            const std::map<std::string, Rect>& Tiles() const { return mTiles; }

            void GenerateTiles(int tileWidth, int tileHeight);

            Rect& GetTileRect(std::string name);
            RectUVs GetTileRectUV(std::string name);

            int Rows() const { return rows; }
            int Columns() const { return columns; }

            void ExportTOML(std::string filepath);

        private:
            int rows, columns, tw, th;
            std::shared_ptr<Texture2D> mTexture;
            std::map<std::string, Rect> mTiles;
        };
    }

}