#include "toml.hpp"
#include "glm/ext/vector_int2.hpp"
#include "toml/value.hpp"
#include <Phoenix/gfx/TextureAtlas.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>

#include <fmt/format.h>

namespace phnx {
namespace gfx {
    glm::vec2 TextureAtlas::GetUV(const glm::ivec2& point) {
        return glm::vec2 {
            (float) point.x / mTexture->Width(),
            (float) point.y / mTexture->Height()
        };
    }

    void TextureAtlas::GenerateTiles(int tileWidth, int tileHeight) {
        
        int rows = mTexture->Height() / tileHeight;
        int cols = mTexture->Width() / tileWidth;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                int x = col * tileWidth;
                int y = row * tileHeight;

                mTiles[fmt::format("tile_{}_{}", col, row)] = Rect {x, y, tileWidth, tileHeight};
            }
        }

        columns = cols;
        this->rows = rows;

        tw = tileWidth;
        th = tileHeight;
    }

    Rect& TextureAtlas::GetTileRect(std::string name) {
        return mTiles[name];
    }

    RectUVs TextureAtlas::GetTileRectUV(std::string name) {
        Rect rect = GetTileRect(name);
        glm::vec2 p0 = {rect.X, rect.Y};
        glm::vec2 p1 = {rect.X + rect.Width, rect.Y + rect.Height};

        return RectUVs {
            p0 / mTexture->Size(),
            p1 / mTexture->Size()
        };
    }

    void TextureAtlas::ExportTOML(std::string filepath) {
        toml::value v;
        toml::value meta;
        meta["Rows"] = rows;
        meta["Columns"] = columns;
        meta["TileWidth"] = tw;
        meta["TileHeight"] = th;
        if (!(mTexture->Filepath().empty())) {
            meta["Filepath"] = mTexture->Filepath();
        }
        v["Metadata"] = meta;

        toml::value tiles;
        for (auto& entry : mTiles) {
            toml::value tile;
            tile["Width"] = entry.second.Width;
            tile["Height"] = entry.second.Height;
            tile["X"] = entry.second.X;
            tile["Y"] = entry.second.Y;

            tiles[entry.first] = tile;
        }

        v["Tiles"] = tiles;
        std::ofstream ostream(filepath);

        ostream << std::setw(80) << v << std::endl; 

        ostream.close();
    }
}
}