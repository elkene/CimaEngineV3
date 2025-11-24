#pragma once

#include <vector>
#include <memory>
#include "Juego/Figuras/Figura.hpp"
#include "../../Motor/Primitivos/Objetos.hpp"

namespace IVJ {

    [[maybe_unused]] void SistemaMovimientoEntes(const std::vector<std::shared_ptr<CE::Objeto>>& entes, float dt);
    [[maybe_unused]] bool SistemaColAABB(CE::Objeto& A, CE::Objeto& B, bool resolucion=false);
    [[maybe_unused]] bool SistemaColAABBMid(CE::Objeto& A, CE::Objeto& B, bool resolucion=false);

    void MoverRectangulo(std::shared_ptr<CE::Objeto> e, float dt, float altoVentana);
    void MoverTriangulo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana);
    void MoverCirculo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentan);
    void MoverJugador(std::shared_ptr<CE::Objeto> e, float dt, float altoVentana);
    void MoverEnemigo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentana);

} // namespace IVJ
