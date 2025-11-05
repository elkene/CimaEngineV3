#pragma once

#include <vector>
#include <memory>
#include "Juego/Figuras/Figura.hpp"

namespace IVJ {

    [[maybe_unused]] void SistemaMovimientoEntes(const std::vector<std::shared_ptr<CE::Objeto>>& entes, float dt);

    void MoverRectangulo(std::shared_ptr<CE::Objeto> e, float dt, float altoVentana);
    void MoverTriangulo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana);
    void MoverCirculo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentan);

} // namespace IVJ
