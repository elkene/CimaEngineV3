#include "TileMap.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include <fstream>
#include <iostream>
namespace IVJ
{
    bool TileMap::loadTileMap(const std::string& atlas_path)
    {
        std::ifstream archivo {atlas_path};
        std::string info;
        archivo >> info; //tag [info]
        archivo>>atlas_p>>atlasW>>atlasH>>
        tileW>>tileH>>map_r>>map_c>>info;
        tiles_vertex.setPrimitiveType(sf::PrimitiveType::Triangles);
        tiles_vertex.resize(map_r*map_c*6);

        if (!atlas_texture.loadFromFile(ASSETS+atlas_p))
        {
            std::cerr<<"[TileMap] No se pudo cargar la imagen "<<atlas_p<<"\n";
            return false;
        }
        int id=0;
        int i=0;
        int j=0;
        int max_col=atlasW/tileW;

        while(archivo>>id)
        {
            if (id!=-1)//no ignorar title
            {
                //Referencia al triangulo a dibujar
                sf::Vertex *trian = &tiles_vertex[(i+j*map_c)*6];
                //posicion del title en el atlas
                int tU=id%max_col;
                int tV=id/max_col;
                //Vertices del trianulo
                trian[0].position = sf::Vector2f(i * tileW, j * tileH);
                trian[1].position = sf::Vector2f((i + 1) * tileW, j * tileH);
                trian[2].position = sf::Vector2f(i * tileW, (j + 1) * tileH);
                trian[3].position = sf::Vector2f(i * tileW, (j + 1) * tileH);
                trian[4].position = sf::Vector2f((i + 1) * tileW, j * tileH);
                trian[5].position = sf::Vector2f((i + 1) * tileW, (j + 1) * tileH);

                // textura del triángulo
                trian[0].texCoords = sf::Vector2f(tU * tileW, tV * tileH);
                trian[1].texCoords = sf::Vector2f((tU + 1) * tileW, tV * tileH);
                trian[2].texCoords = sf::Vector2f(tU * tileW, (tV + 1) * tileH);
                trian[3].texCoords = sf::Vector2f(tU * tileW, (tV + 1) * tileH);
                trian[4].texCoords = sf::Vector2f((tU + 1) * tileW, tV * tileH);
                trian[5].texCoords = sf::Vector2f((tU + 1) * tileW, (tV + 1) * tileH);
            }
            if((i+1)%map_c==0)++j;
            ++i%=map_c;
        }
        return true;
    }
    void TileMap::draw(sf::RenderTarget& target,sf::RenderStates state)const
    {
        state.transform*=getTransform();
        state.texture=&atlas_texture;
        target.draw(tiles_vertex,state);
    }
}