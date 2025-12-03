#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <map>

namespace IVJ
{
    class TileMap : public sf::Transformable, public sf::Drawable
    {
    public:
        explicit TileMap() = default;
        bool loadTileMap(const std::string& jsonPath);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        // Nuevo método para configurar el modo infinito horizontal
        void setModoInfinitoHorizontal(bool infinito, const sf::Vector2f& areaVisible = sf::Vector2f(1920, 1080));

        // Método para actualizar la posición de la cámara
        void setPosicionCamara(const sf::Vector2f& posicionCamara);

        // Nuevos métodos para dibujar en capas separadas
        void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawForeground(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        struct TileRef {
            int index;
            int x;
            int y;
        };

        struct Layer {
            sf::VertexArray vertices;
            sf::Texture texture;
            std::string name;
            bool hidden = false;
            std::map<int, TileRef> tileRefs;
            bool hasTiles = false;
            float depth = 0.0f; // Profundidad del layer para ordenamiento
            float parallaxFactor = 1.0f; // Factor de velocidad parallax (0.0 = estático, 1.0 = velocidad normal)
        };

        std::vector<Layer> layers;

        int mapWidth{};
        int mapHeight{};
        int tileWidth{};
        int tileHeight{};
        int numLayers{};
        int tilesWide{};
        std::string atlasDir{};
        bool separateFiles{};
        std::string fileNamePrefix{};

        // Variables para modo infinito horizontal
        bool modoInfinitoHorizontal{true};
        sf::Vector2f areaVisible{1920, 1080};
        sf::Vector2f posicionCamara{0, 0};

        // Método para actualizar los vértices en modo infinito horizontal
        void actualizarVerticesInfinitosHorizontales();
    };
}