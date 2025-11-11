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
      :IComponentes{},m_sprite{textura}
    {
      m_sprite.setScale({escala,escala});
    }
}
