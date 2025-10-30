#include <cmath>

#include "Sistemas.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "Juego/Figuras/Triangulo.hpp"

namespace IVJ {
    void SistemaMovimientoTriangulo(const std::vector<std::shared_ptr<Triangulo> > &tri, float dt) {
        for (auto& t : tri) {
            if (t->tieneComponente<CE::ITimer>()) {
                auto& timer=*t->getComponente<CE::ITimer>();
                auto trans=t->getTransformada();
                //trans->posicion.x+=80*dt;
                //trans->posicion.y+=5*dt;
                //timer.frame_actual++;


                // Inicializa velocidad si es 0
                if (trans->velocidad.magnitud() == 0)
                    //posicion donde comenzaran a movese
                        trans->velocidad = CE::Vector2D{100.0f, 500.0f}; //velocidad inicial

                        // Movimiento horizontal
                        trans->posicion.x += trans->velocidad.x * dt;

                        // Movimiento onda vertical
                        //trans->posicion.y += std::sin(timer.frame_actual * dt * 5.0f) * 20.0f;
                        //trans->fase = static_cast<float>(rand() % 360);
                        //trans->posicion.y += std::sin((timer.frame_actual * dt * 2.0f) + trans->fase) * 8.0f;

                        trans->posicion.y += std::sin((timer.frame_actual * dt * 2.0f)+trans->fase * 50.0f);

                        // Rebote horizontal
                        if (trans->posicion.x <  0 || trans->posicion.x > 1200 )
                            trans->velocidad.x *= -1;

                        timer.frame_actual++;

            }
        }
    }
}
