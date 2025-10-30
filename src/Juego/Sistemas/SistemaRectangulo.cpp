#include "Sistemas.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "Juego/Figuras/Rectangulo.hpp"

namespace IVJ {
    void SistemaMovimientoRectangulo(const std::vector<std::shared_ptr<Rectangulo> > &rects, float dt) {
        for (auto& r : rects) {
            if (r->tieneComponente<CE::ITimer>()) {
                auto& timer=*r->getComponente<CE::ITimer>();
                auto trans=r->getTransformada();
                //Movimiento basico hacia abajo
                //trans->posicion.x+=5*dt;
                //trans->posicion.y+=80*dt;
                //timer.frame_actual++;

                // Inicializa la velocidad si es 0
                if (trans->velocidad.magnitud() == 0)
                    trans->velocidad = CE::Vector2D{0.0f, 100.0f};

                // Actualiza posición
                trans->posicion.x += trans->velocidad.x * dt;
                trans->posicion.y += trans->velocidad.y * dt;

                // Rebote vertical //al tener un limite si la figura wse genera fuera del limite se buguea cambiar 1200 para probar
                if (trans->posicion.y < 0 || trans->posicion.y > 1200.0f)
                    trans->velocidad.y *= -1;

                timer.frame_actual++;
                //trans->posicion.y+=50*dt; //velocidad vertical
                //if (trans->posicion.y>100) //limite ventana(ejemplo de 100px)
                  //trans->posicion.y+=10*dt;

            }
        }
    }
}
