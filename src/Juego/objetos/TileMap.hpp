#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace IVJ
{
    class TileMap : public sf::Transformable, public sf::Drawable
    {
    public:
        explicit TileMap() = default;
        bool loadTileMap(const std::string& jsonPath);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        struct Layer {
            sf::VertexArray vertices;
            sf::Texture texture;
            std::string name;
            bool hidden = false;
        };

        std::vector<Layer> layers;

        int mapWidth{};
        int mapHeight{};
        int tileWidth{};
        int tileHeight{};
        int numLayers{};
        std::string atlasPath{};
    };
}
