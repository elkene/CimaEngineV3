#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

namespace IVJ
{
    class TileMap : public sf::Transformable, public sf::Drawable
    {
    public:
        explicit TileMap() = default;

        bool loadTileMap(const std::string& atlasPath);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        int atlasW{};   // ancho del atlas
        int atlasH{};   // alto del atlas
        int tileW{};    // ancho de cada tile
        int tileH{};    // alto de cada tile
        int mapR{};     // filas del mapa
        int mapC{};     // columnas del mapa

        std::string atlasP{};       // ruta del atlas
        sf::VertexArray tilesVertex; // vértices para dibujar tiles
        sf::Texture atlasTexture;    // textura del atlas
    };
}
