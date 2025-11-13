#include "TileMap.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <fstream>
#include <iostream>

namespace IVJ
{
    bool TileMap::loadTileMap(const std::string& atlasPath)
    {
        std::ifstream archivo{atlasPath};
        if (!archivo.is_open())
        {
            std::cerr << "[TileMap] No se pudo abrir el archivo: " << atlasPath << "\n";
            return false;
        }

        std::string info;
        archivo >> info; // tag [info]

        archivo >> atlasP >> atlasW >> atlasH
                >> tileW >> tileH >> mapR >> mapC >> info;

        tilesVertex.setPrimitiveType(sf::PrimitiveType::Triangles);
        tilesVertex.resize(mapR * mapC * 6);

        if (!atlasTexture.loadFromFile(ASSETS + atlasP))
        {
            std::cerr << "[TileMap] No se pudo cargar la imagen: " << atlasP << "\n";
            return false;
        }

        int id = 0;
        int i = 0;
        int j = 0;
        int maxCol = atlasW / tileW;

        while (archivo >> id)
        {
            if (id != -1) // no ignorar tile
            {
                // referencia al triángulo a dibujar
                sf::Vertex* tri = &tilesVertex[(i + j * mapC) * 6];

                // posición del tile en el atlas
                int tU = id % maxCol;
                int tV = id / maxCol;

                // vértices del rectángulo (2 triángulos)
                tri[0].position = sf::Vector2f(i * tileW, j * tileH);
                tri[1].position = sf::Vector2f((i + 1) * tileW, j * tileH);
                tri[2].position = sf::Vector2f(i * tileW, (j + 1) * tileH);
                tri[3].position = sf::Vector2f(i * tileW, (j + 1) * tileH);
                tri[4].position = sf::Vector2f((i + 1) * tileW, j * tileH);
                tri[5].position = sf::Vector2f((i + 1) * tileW, (j + 1) * tileH);

                // coordenadas de textura
                tri[0].texCoords = sf::Vector2f(tU * tileW, tV * tileH);
                tri[1].texCoords = sf::Vector2f((tU + 1) * tileW, tV * tileH);
                tri[2].texCoords = sf::Vector2f(tU * tileW, (tV + 1) * tileH);
                tri[3].texCoords = sf::Vector2f(tU * tileW, (tV + 1) * tileH);
                tri[4].texCoords = sf::Vector2f((tU + 1) * tileW, tV * tileH);
                tri[5].texCoords = sf::Vector2f((tU + 1) * tileW, (tV + 1) * tileH);
            }

            if ((i + 1) % mapC == 0) ++j;
            i = (i + 1) % mapC;
        }

        return true;
    }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &atlasTexture;
        target.draw(tilesVertex, states);
    }
}
