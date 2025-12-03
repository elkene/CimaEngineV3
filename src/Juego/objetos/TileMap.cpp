#include "TileMap.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

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
        tilesWide  = j["tileset"]["tilesWide"].get<int>();

        // Extraer configuración de exportación
        atlasDir = j["settings"]["ExportImagePanel_prefPath"].get<std::string>();
        fileNamePrefix = j["settings"]["ExportImagePanel_prefFileName"].get<std::string>();
        separateFiles = j["settings"]["ExportImagePanel_prefSeparateFiles"].get<std::string>() == "true";

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

            // Leer la profundidad (depth) si existe, sino usar 0.0f por defecto
            if (layerData.contains("depth")) {
                layer.depth = layerData["depth"].get<float>();
            } else {
                layer.depth = 0.0f;
            }

            // Leer el parallax factor si existe, sino calcularlo automáticamente desde depth
            if (layerData.contains("parallaxFactor")) {
                layer.parallaxFactor = layerData["parallaxFactor"].get<float>();
            } else {
                // Calcular parallax automáticamente: mayor depth = más cerca = más rápido
                layer.parallaxFactor = 0.1f + (layer.depth / 12.0f) * 0.9f;
            }

            std::cout << "[TileMap] Capa " << layerName
                      << " - Depth: " << layer.depth
                      << " - Parallax: " << layer.parallaxFactor << "\n";

            // Construir ruta de la textura usando el NOMBRE DEL LAYER
            std::string texturePath;
            if (separateFiles) {
                texturePath = atlasDir + "/" + layerName + ".png";
            } else {
                texturePath = atlasDir + "/" + fileNamePrefix + ".png";
            }

            std::cout << "[TileMap] Intentando cargar textura para capa " << i
                      << " (" << layerName << "): " << texturePath << "\n";

            // Cargar textura para esta capa
            if (!layer.texture.loadFromFile(texturePath))
            {
                std::cerr << "[TileMap] No se pudo cargar la textura para la capa " << layerName
                          << ": " << texturePath << "\n";

                std::string fallbackPath = atlasDir + "/" + fileNamePrefix + std::to_string(i) + ".png";
                std::cout << "[TileMap] Intentando ruta alternativa: " << fallbackPath << "\n";

                if (!layer.texture.loadFromFile(fallbackPath))
                {
                    std::cerr << "[TileMap] También falló la ruta alternativa: " << fallbackPath << "\n";
                    continue;
                }
            }

            layer.texture.setRepeated(true);
            layer.texture.setSmooth(true);

            // Cargar tileRefs si existen
            if (layerData.contains("tileRefs") && !layerData["tileRefs"].empty())
            {
                auto tileRefsData = layerData["tileRefs"];
                layer.hasTiles = true;

                for (auto& [key, tileData] : tileRefsData.items())
                {
                    TileRef tileRef;
                    tileRef.index = tileData["index"].get<int>();
                    tileRef.x = tileData["x"].get<int>();
                    tileRef.y = tileData["y"].get<int>();
                    layer.tileRefs[std::stoi(key)] = tileRef;
                }

                // Crear vertex array para tiles
                layer.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
                layer.vertices.resize(layer.tileRefs.size() * 6);

                int vertexIndex = 0;
                for (const auto& [position, tileRef] : layer.tileRefs)
                {
                    int tilesPerRow = mapWidth / tileWidth;
                    int tileX = position % tilesPerRow;
                    int tileY = position / tilesPerRow;

                    float posX = tileX * tileWidth;
                    float posY = tileY * tileHeight;

                    float texLeft = static_cast<float>(tileRef.x);
                    float texTop = static_cast<float>(tileRef.y);
                    float texRight = texLeft + tileWidth;
                    float texBottom = texTop + tileHeight;

                    sf::Vertex* triangles = &layer.vertices[vertexIndex * 6];

                    // Triángulo 1
                    triangles[0].position = sf::Vector2f(posX, posY);
                    triangles[1].position = sf::Vector2f(posX + tileWidth, posY);
                    triangles[2].position = sf::Vector2f(posX, posY + tileHeight);
                    triangles[0].texCoords = sf::Vector2f(texLeft, texTop);
                    triangles[1].texCoords = sf::Vector2f(texRight, texTop);
                    triangles[2].texCoords = sf::Vector2f(texLeft, texBottom);

                    // Triángulo 2
                    triangles[3].position = sf::Vector2f(posX, posY + tileHeight);
                    triangles[4].position = sf::Vector2f(posX + tileWidth, posY);
                    triangles[5].position = sf::Vector2f(posX + tileWidth, posY + tileHeight);
                    triangles[3].texCoords = sf::Vector2f(texLeft, texBottom);
                    triangles[4].texCoords = sf::Vector2f(texRight, texTop);
                    triangles[5].texCoords = sf::Vector2f(texRight, texBottom);

                    vertexIndex++;
                }
            }
            else
            {
                // Si no hay tileRefs, crear un fondo plano con parallax
                layer.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
                layer.vertices.resize(6);

                // Ancho extendido para cubrir toda el área
                float anchoFondo = areaVisible.x * 6.0f; // Más ancho para evitar bordes
                float altoFondo = mapHeight;

                sf::Vertex* tri = &layer.vertices[0];

                // Centrar verticalmente
                float posY = (areaVisible.y - altoFondo) / 2.0f;

                // IMPORTANTE: Posiciones iniciales sin offset
                // El offset se aplicará dinámicamente en draw()
                tri[0].position = {-anchoFondo/2, posY};
                tri[1].position = {anchoFondo/2, posY};
                tri[2].position = {-anchoFondo/2, posY + altoFondo};
                tri[3].position = {-anchoFondo/2, posY + altoFondo};
                tri[4].position = {anchoFondo/2, posY};
                tri[5].position = {anchoFondo/2, posY + altoFondo};

                // Textura repetida
                sf::Vector2u textureSize = layer.texture.getSize();
                float repeatX = anchoFondo / textureSize.x;

                tri[0].texCoords = {0, 0};
                tri[1].texCoords = {textureSize.x * repeatX, 0};
                tri[2].texCoords = {0, static_cast<float>(textureSize.y)};
                tri[3].texCoords = {0, static_cast<float>(textureSize.y)};
                tri[4].texCoords = {textureSize.x * repeatX, 0};
                tri[5].texCoords = {textureSize.x * repeatX, static_cast<float>(textureSize.y)};
            }

            layers.push_back(std::move(layer));
        }

        if (layers.empty()) {
            std::cerr << "[TileMap] No se pudo cargar ninguna capa.\n";
            return false;
        }

        // Ordenar las capas por profundidad
        std::sort(layers.begin(), layers.end(),
            [](const Layer& a, const Layer& b) {
                return a.depth < b.depth;
            });

        std::cout << "[TileMap] Mapa cargado desde JSON: " << jsonPath
                  << " con " << layers.size() << " capas cargadas exitosamente.\n";

        return true;
    }

    void TileMap::setModoInfinitoHorizontal(bool infinito, const sf::Vector2f& areaVisible)
    {
        this->modoInfinitoHorizontal = infinito;
        this->areaVisible = areaVisible;

        for (auto& layer : layers) {
            layer.texture.setRepeated(infinito);
        }
    }

    void TileMap::setPosicionCamara(const sf::Vector2f& posicionCamara)
    {
        this->posicionCamara = posicionCamara;
    }

    void TileMap::actualizarVerticesInfinitosHorizontales()
    {
        // Ya no necesitamos este método, el parallax se maneja en draw()
    }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (const auto& layer : layers)
        {
            if (layer.hidden) continue;

            // Crear transformación específica para esta capa
            sf::RenderStates layerStates = states;

            if (!layer.hasTiles) {
                // Aplicar offset parallax basado en el factor de la capa
                // Cada capa se mueve a diferente velocidad creando el efecto de profundidad
                float offsetX = -posicionCamara.x * layer.parallaxFactor;

                // Wrapping suave para bucle infinito
                sf::Vector2u texSize = layer.texture.getSize();
                float wrappedOffset = std::fmod(offsetX, static_cast<float>(texSize.x));
                if (wrappedOffset > 0) wrappedOffset -= texSize.x;

                sf::Transform layerTransform;
                layerTransform.translate(sf::Vector2f(wrappedOffset, 0.f));

                layerStates.transform *= layerTransform;
            }

            layerStates.texture = &layer.texture;
            target.draw(layer.vertices, layerStates);
        }
    }

    void TileMap::drawBackground(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        // Solo dibujar Layer0 (fondo)
        for (const auto& layer : layers)
        {
            if (layer.hidden) continue;
            if (layer.name != "Layer0") continue;

            sf::RenderStates layerStates = states;

            if (!layer.hasTiles) {
                float offsetX = -posicionCamara.x * layer.parallaxFactor;

                sf::Vector2u texSize = layer.texture.getSize();
                float wrappedOffset = std::fmod(offsetX, static_cast<float>(texSize.x));
                if (wrappedOffset > 0) wrappedOffset -= texSize.x;

                sf::Transform layerTransform;
                layerTransform.translate(sf::Vector2f(wrappedOffset, 0.f));

                layerStates.transform *= layerTransform;
            }

            layerStates.texture = &layer.texture;
            target.draw(layer.vertices, layerStates);
        }
    }

    void TileMap::drawForeground(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        // Dibujar todas las capas EXCEPTO Layer0
        for (const auto& layer : layers)
        {
            if (layer.hidden) continue;
            if (layer.name == "Layer0") continue;

            sf::RenderStates layerStates = states;

            if (!layer.hasTiles) {
                float offsetX = -posicionCamara.x * layer.parallaxFactor;

                sf::Vector2u texSize = layer.texture.getSize();
                float wrappedOffset = std::fmod(offsetX, static_cast<float>(texSize.x));
                if (wrappedOffset > 0) wrappedOffset -= texSize.x;

                sf::Transform layerTransform;
                layerTransform.translate(sf::Vector2f(wrappedOffset, 0.f));

                layerStates.transform *= layerTransform;
            }

            layerStates.texture = &layer.texture;
            target.draw(layer.vertices, layerStates);
        }
    }
}