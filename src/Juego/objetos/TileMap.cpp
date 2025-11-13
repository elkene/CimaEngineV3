#include "TileMap.hpp"
#include <fstream>
#include <iostream>

namespace IVJ
{
    using json = nlohmann::json;

    bool TileMap::loadTileMap(const std::string& jsonPath)
    {
        std::ifstream archivo(jsonPath);
        if (!archivo.is_open())
        {
            std::cerr << "[TileMap] No se pudo abrir el archivo JSON: " << jsonPath << "\n";
            return false;
        }

        json j;
        archivo >> j;

        // Extraer datos base
        mapWidth   = j["canvas"]["width"].get<int>();
        mapHeight  = j["canvas"]["height"].get<int>();
        tileWidth  = j["tileset"]["tileWidth"].get<int>();
        tileHeight = j["tileset"]["tileHeight"].get<int>();
        numLayers  = j["canvas"]["numLayers"].get<int>();

        // Construir ruta del atlas
        std::string atlasName = j["settings"]["ExportImagePanel_prefFileName"].get<std::string>() + ".png";
        std::string atlasDir  = j["settings"]["ExportImagePanel_prefPath"].get<std::string>();
        atlasPath = atlasDir + "/" + atlasName;

        // Cargar textura del atlas
        sf::Texture atlasTexture;
        if (!atlasTexture.loadFromFile(atlasPath))
        {
            std::cerr << "[TileMap] No se pudo cargar el atlas: " << atlasPath << "\n";
            return false;
        }

        atlasTexture.setRepeated(true);
        atlasTexture.setSmooth(true);

        // Escala del fondo (opción 1)
        const float scaleFactor = 4.0f; // ajusta este valor a tu gusto

        // Crear una capa por cada layer
        for (int i = 0; i < numLayers; ++i)
        {
            std::string idx = std::to_string(i);
            auto layerData = j["canvas"]["layers"][idx];
            bool hidden = layerData["hidden"].get<bool>();
            std::string layerName = layerData["name"].get<std::string>();

            Layer layer;
            layer.name = layerName;
            layer.hidden = hidden;
            layer.texture = atlasTexture;
            layer.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
            layer.vertices.resize(6); // fondo plano

            if (!hidden)
            {
                sf::Vertex* tri = &layer.vertices[0];

                // Posiciones escaladas
                float scaledWidth  = mapWidth * scaleFactor;
                float scaledHeight = mapHeight * scaleFactor;

                tri[0].position = {0, 0};
                tri[1].position = {scaledWidth, 0};
                tri[2].position = {0, scaledHeight};
                tri[3].position = {0, scaledHeight};
                tri[4].position = {scaledWidth, 0};
                tri[5].position = {scaledWidth, scaledHeight};

                // Coordenadas de textura (no se escalan)
                tri[0].texCoords = {0, 0};
                tri[1].texCoords = {static_cast<float>(mapWidth), 0};
                tri[2].texCoords = {0, static_cast<float>(mapHeight)};
                tri[3].texCoords = {0, static_cast<float>(mapHeight)};
                tri[4].texCoords = {static_cast<float>(mapWidth), 0};
                tri[5].texCoords = {static_cast<float>(mapWidth), static_cast<float>(mapHeight)};
            }

            layers.push_back(std::move(layer));
        }

        std::cout << "[TileMap] Mapa cargado desde JSON: " << jsonPath
                  << " con " << layers.size() << " capas.\n";
        return true;
    }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (const auto& layer : layers)
        {
            if (layer.hidden) continue;
            states.texture = &layer.texture;
            target.draw(layer.vertices, states);
        }
    }
}
