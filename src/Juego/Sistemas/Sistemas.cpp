#include "Sistemas.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"

namespace IVJ {
    void SistemaMovimientoEntes(const std::vector<std::shared_ptr<CE::Objeto> > &entes, float dt) {
        for (auto& e : entes) {
            if (e->tieneComponente<CE::ITimer>()) {
                auto& timer=*e->getComponente<CE::ITimer>();
                auto trans=e->getTransformada();
                trans->posicion.x+=5*dt;
                trans->posicion.y+=80*dt;
                timer.frame_actual++;
            }
        }
    }
}