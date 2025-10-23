#include "IComponentes.hpp"

namespace CE
{
    INombre::INombre(const std::string& nom)
        : nombre(std::move(nom)) {}

    ITransform::ITransform(const Vector2D& pos, const Vector2D& vel, float ang)
        : posicion{pos},
          pos_previa(pos),
          velocidad(vel),
          angulo{ang},
          centroX(0.f),
          centroY(0.f),
          radio(0.f),
          inicializado(false) {}

    ITimer::ITimer()
        : frame_actual(0) {}
}
