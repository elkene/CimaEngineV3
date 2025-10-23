#pragma once

#include <vector>
#include <memory>
#include "../../Motor/Componentes/IComponentes.hpp"
#include "Juego/Figuras/Figura.hpp"

namespace IVJ {

    // Funciones de movimiento por figura
    void MoverRectangulo(std::shared_ptr<CE::Objeto> e, float dt, float altoVentana);
    void MoverTriangulo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana);
    void MoverCirculo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentana);

    // Sistema principal que recorre todos los objetos y aplica su movimiento
    void SistemaMovimientoEntes(
        const std::vector<std::shared_ptr<CE::Objeto>>& entes,
        float dt,
        float anchoVentana,
        float altoVentana
    );

} // namespace IVJ
