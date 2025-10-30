#include <cmath>

#include "Sistemas.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "Juego/Figuras/Circulo.hpp"

namespace IVJ {
    void SistemaMovimientoCirculo(const std::vector<std::shared_ptr<Circulo>>& circs, float dt) {
        for (auto& c : circs) {
            if (c->tieneComponente<CE::ITimer>()) {
                auto& timer = *c->getComponente<CE::ITimer>();
                auto trans = c->getTransformada();

                // Inicializa velocidad angular y centro si no existe
                if (trans->velocidad.magnitud() == 0) {
                    trans->velocidad = CE::Vector2D{ 100.f, 0.f }; // velocidad angular
                    trans->angulo = static_cast<float>(rand() % 360); // ángulo inicial único
                    trans->centro = trans->posicion; // centro en su posición original
                }

                // Movimiento del centro (traslación)
                trans->centro.x += trans->velocidad.x * dt;
                trans->centro.y += trans->velocidad.y * dt;



                // Rotación alrededor de su propio centro (órbita)
                trans->angulo += 200.f * dt; // velocidad angular
                if (trans->angulo > 360.f) trans->angulo -= 360.f;

                // Rebote horizontal
                if (trans->centro.x - 50.0f < 0.f) {
                    trans->centro.x = 50.0f;          // lo colocas dentro del límite
                    trans->velocidad.x *= -1;           // inviertes dirección
                }
                else if (trans->centro.x + 50.0f > 1200.f) {
                    trans->centro.x = 1200.f - 50.0f;
                    trans->velocidad.x *= -1;
                }

                trans->angulo += 5.f * dt; // velocidad de giro


                trans->posicion.x = trans->centro.x + 50.0f * cos(trans->angulo * 3.14159f / 180.f);
                trans->posicion.y = trans->centro.y + 50.0f * sin(trans->angulo * 3.14159f / 180.f);

                timer.frame_actual++;
            }
        }
    }
}