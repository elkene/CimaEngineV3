#include "Sistema.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "Juego/Figuras/Figura.hpp"
#include <cmath>
#include "../Transformada/Transformada.h"
namespace IVJ
{
    // Movimiento de rectángulos (arriba/abajo con rebote)
    void MoverRectangulo(std::shared_ptr<CE::Objeto> e, float dt, float altoVentana)
    {
        auto trans = e->getTransformada();
        trans->posicion.y += trans->velocidad.y * dt;

        if (trans->posicion.y < 0.f || trans->posicion.y > altoVentana)
            trans->velocidad.y = -trans->velocidad.y;
    }

    // Movimiento de triángulos (onda horizontal con rebote)

    void MoverTriangulo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentana)
    {
        auto trans = e->getTransformada();

        // Movimiento horizontal constante
        trans->posicion.x += trans->velocidad.x * dt;

        // Movimiento vertical en forma de onda senoidal
        float amplitud = 50.f;        // Altura de la onda
        float frecuencia = 2.f;       // Número de oscilaciones
        trans->posicion.y = (altoVentana / 2.f) + amplitud * std::sin(trans->posicion.x * frecuencia * 0.01f);

        // Rebote en los bordes de la ventana
        if (trans->posicion.x < 0.f || trans->posicion.x > anchoVentana)
        {
            trans->velocidad.x = -trans->velocidad.x; // invertir dirección
        }
    }


    // Movimiento de círculos (trayectoria circular, fase y radio independientes)

    void MoverCirculo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentana)
    {
        auto trans = e->getTransformada();

        // Si aún no se inicializó el centro y radio, lo configuramos por defecto
        if (!trans->inicializado) {
            trans->centroX = trans->posicion.x / 2.f;
            trans->centroY = altoVentana / 2.f;
            trans->radio   = 100.f;
            trans->inicializado = true;
        }

        // Usamos la velocidad.x como "velocidad angular"
        trans->angulo += trans->velocidad.x - dt;

        // Movimiento circular con centro dinámico
        trans->posicion.x = trans->centroX + trans->radio * std::cos(trans->angulo);
        trans->posicion.y = trans->centroY + trans->radio * std::sin(trans->angulo);

        // Hacemos que el centro se mueva lateralmente como el rectángulo
        trans->centroX += trans->velocidad.y * dt;

        // Rebote horizontal
        if (trans->centroX - trans->radio < 0.f || trans->centroX + trans->radio > anchoVentana) {
            trans->velocidad.y = -trans->velocidad.y;
        }
    }




    // Sistema principal
    void SistemaMovimientoEntes(
        const std::vector<std::shared_ptr<CE::Objeto>>& entes,
        float dt,
        float anchoVentana,
        float altoVentana)
    {
        for (auto& e : entes)
        {
            if (!e->tieneComponente<CE::ITimer>()) continue;

            if (std::dynamic_pointer_cast<IVJ::Rectangulo>(e))
                IVJ::MoverRectangulo(e, dt, altoVentana);
            else if (std::dynamic_pointer_cast<IVJ::Triangulo>(e))
                IVJ::MoverTriangulo(e, dt, anchoVentana, altoVentana);
            else if (std::dynamic_pointer_cast<IVJ::Circulo>(e))
                IVJ::MoverCirculo(e, dt, anchoVentana, altoVentana);
        }
    }
}
// namespace IVJ
