#include "TileMap.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

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

            // Construir ruta de la textura usando el NOMBRE DEL LAYER
            std::string texturePath;
            if (separateFiles) {
                // Usar el nombre exacto del layer (Layer0, Layer1, etc.)
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

                // Intentar con formato alternativo (usando el índice)
                std::string fallbackPath = atlasDir + "/" + fileNamePrefix + std::to_string(i) + ".png";
                std::cout << "[TileMap] Intentando ruta alternativa: " << fallbackPath << "\n";

                if (!layer.texture.loadFromFile(fallbackPath))
                {
                    std::cerr << "[TileMap] También falló la ruta alternativa: " << fallbackPath << "\n";
                    continue; // Saltar esta capa
                }
            }

            // Para modo infinito horizontal, activar repeated solo en X
            if (modoInfinitoHorizontal) {
                layer.texture.setRepeated(true);
            } else {
                layer.texture.setRepeated(false);
            }
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
                    // Calcular posición en el mapa
                    int tilesPerRow = mapWidth / tileWidth;
                    int tileX = position % tilesPerRow;
                    int tileY = position / tilesPerRow;

                    float posX = tileX * tileWidth;
                    float posY = tileY * tileHeight;

                    // Calcular coordenadas de textura en el atlas
                    float texLeft = static_cast<float>(tileRef.x);
                    float texTop = static_cast<float>(tileRef.y);
                    float texRight = texLeft + tileWidth;
                    float texBottom = texTop + tileHeight;

                    // Definir los 6 vértices para 2 triángulos
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
                // Si no hay tileRefs, crear un fondo plano
                layer.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

                if (modoInfinitoHorizontal) {
                    // En modo infinito horizontal, crear un fondo que se repita solo en X
                    layer.vertices.resize(6);

                    // El fondo tiene altura fija pero ancho infinito
                    float anchoFondo = areaVisible.x * 4; // 4 veces el ancho visible
                    float altoFondo = mapHeight; // Altura original del mapa

                    sf::Vertex* tri = &layer.vertices[0];

                    // Centrar verticalmente, pero extender horizontalmente
                    float posY = (areaVisible.y - altoFondo) / 2.0f; // Centrar verticalmente

                    tri[0].position = {-anchoFondo/2, posY};
                    tri[1].position = {anchoFondo/2, posY};
                    tri[2].position = {-anchoFondo/2, posY + altoFondo};
                    tri[3].position = {-anchoFondo/2, posY + altoFondo};
                    tri[4].position = {anchoFondo/2, posY};
                    tri[5].position = {anchoFondo/2, posY + altoFondo};

                    // Textura repetida solo horizontalmente
                    sf::Vector2u textureSize = layer.texture.getSize();
                    float repeatX = anchoFondo / textureSize.x;

                    tri[0].texCoords = {0, 0};
                    tri[1].texCoords = {textureSize.x * repeatX, 0};
                    tri[2].texCoords = {0, static_cast<float>(textureSize.y)};
                    tri[3].texCoords = {0, static_cast<float>(textureSize.y)};
                    tri[4].texCoords = {textureSize.x * repeatX, 0};
                    tri[5].texCoords = {textureSize.x * repeatX, static_cast<float>(textureSize.y)};
                } else {
                    // Comportamiento normal (no infinito)
                    layer.vertices.resize(6);

                    const float scaleFactor = 1.0f;
                    float scaledWidth = mapWidth * scaleFactor;
                    float scaledHeight = mapHeight * scaleFactor;

                    sf::Vertex* tri = &layer.vertices[0];

                    tri[0].position = {0, 0};
                    tri[1].position = {scaledWidth, 0};
                    tri[2].position = {0, scaledHeight};
                    tri[3].position = {0, scaledHeight};
                    tri[4].position = {scaledWidth, 0};
                    tri[5].position = {scaledWidth, scaledHeight};

                    // Usar toda la textura para el fondo plano
                    sf::Vector2u textureSize = layer.texture.getSize();
                    tri[0].texCoords = {0, 0};
                    tri[1].texCoords = {static_cast<float>(textureSize.x), 0};
                    tri[2].texCoords = {0, static_cast<float>(textureSize.y)};
                    tri[3].texCoords = {0, static_cast<float>(textureSize.y)};
                    tri[4].texCoords = {static_cast<float>(textureSize.x), 0};
                    tri[5].texCoords = {static_cast<float>(textureSize.x), static_cast<float>(textureSize.y)};
                }
            }

            layers.push_back(std::move(layer));
        }

        if (layers.empty()) {
            std::cerr << "[TileMap] No se pudo cargar ninguna capa.\n";
            return false;
        }

        std::cout << "[TileMap] Mapa cargado desde JSON: " << jsonPath
                  << " con " << layers.size() << " capas cargadas exitosamente.\n";
        return true;
    }

    void TileMap::setModoInfinitoHorizontal(bool infinito, const sf::Vector2f& areaVisible)
    {
        this->modoInfinitoHorizontal = infinito;
        this->areaVisible = areaVisible;

        // Actualizar configuración de texturas
        for (auto& layer : layers) {
            layer.texture.setRepeated(infinito);
        }

        if (infinito) {
            actualizarVerticesInfinitosHorizontales();
        }
    }

    void TileMap::setPosicionCamara(const sf::Vector2f& posicionCamara)
    {
        if (!modoInfinitoHorizontal) return;

        this->posicionCamara = posicionCamara;
        actualizarVerticesInfinitosHorizontales();
    }

    void TileMap::actualizarVerticesInfinitosHorizontales()
    {
        if (!modoInfinitoHorizontal) return;

        // for (auto& layer : layers) {
        //     if (!layer.hasTiles) { // Solo para fondos planos
        //         // Efecto parallax horizontal (más lento que el movimiento del jugador)
        //         float parallaxFactor = 0.3f; // Ajusta este valor (0.0 a 1.0)
        //         float offsetX = -posicionCamara.x * parallaxFactor;
        //
        //         // Mantener la posición vertical centrada
        //         float offsetY = (areaVisible.y - mapHeight) / 2.0f;
        //
        //         // Aplicar transformación
        //         setPosition(offsetX, offsetY);
        //         break;
        //     }
        // }
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