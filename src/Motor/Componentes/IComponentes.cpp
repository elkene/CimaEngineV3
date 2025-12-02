#include "IComponentes.hpp"

namespace CE
{
    INombre::INombre(const std::string& nom)
        :nombre(std::move(nom   )){}

    ITransform::ITransform(const Vector2D& pos, const Vector2D& vel, float ang)
        :posicion{pos},pos_previa(pos),velocidad(vel),angulo{ang}{}

    ITimer::ITimer()
        :frame_actual(0){}

    ISprite::ISprite(const sf::Texture& textura, float escala)
      :IComponentes{},m_sprite{textura}, escala {escala}
    {
      m_sprite.setScale({escala,escala});
        auto dim =textura.getSize();
        width=dim.x;
        height=dim.y;
        //pivote
        m_sprite.setOrigin({dim.x/2.f,dim.y/2.f});
    }
    ISprite::ISprite(const sf::Texture& textura,int w,int h, float escala)
      :IComponentes{},m_sprite{m_textura}, m_textura{textura},
    width{w},height{h},escala{escala}
    {
        m_textura.setSmooth(true);
        m_sprite.setTexture(m_textura);
        m_sprite.setTextureRect(sf::IntRect{{0,0},{w,h}});
        m_sprite.setScale({escala,escala});
        //pivote
        m_sprite.setOrigin({width/2.f,height/2.f});
    }

    IControl::IControl()
    {
        arr=false;
        abj=false;
        izq=false;
        der=false;
        acc=false;
        sacc=false;
        saltar=false;
        correr=false;
    };
    IBoundingBox::IBoundingBox(const Vector2D &dim)
        :tam{dim.x,dim.y}, mitad{dim.x/2,dim.y/2}{}

    }



