#include "IComponentes.hpp"

namespace CE {
    INombre::INombre(const std::string& nom)
        :nombre{std::move(nom)}{}

    ITransform::ITransform()   // <<--- Constructor por defecto agregado
        : posicion{0,0}, pos_prev{0,0}, velocidad{0,0}, angulo{0} {}

    ITransform::ITransform(const CE::Vector2D& pos,const CE::Vector2D& vel,float ang)
        :posicion{pos},pos_prev{pos},velocidad{vel},angulo{ang}{}
    ITimer::ITimer()
        :frame_actual{0}{}
}