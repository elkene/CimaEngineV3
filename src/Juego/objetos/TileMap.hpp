#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include <SFML/Graphics.hpp>

namespace IVJ
{
    class TileMap : public sf::Transformable, public sf::Drawable
    {
        public:
            explicit TileMap()=default;
        public:
            bool loadTileMap(const std::string& atlas_path);
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        private:
            int atlasW{};
            int atlasH{};
            int tileW{};
            int tileH{};
            int map_r{};
            int map_c{};
            std::string atlas_p{};
            sf::VertexArray tiles_vertex;
            sf::Texture atlas_texture;

    };
}
