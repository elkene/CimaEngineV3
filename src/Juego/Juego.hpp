#pragma once
#include <memory>
#include <Motor/App/ALayer.hpp>
#include <optional>

#include "Figuras/Circulo.hpp"
#include "Motor/Utils/Utils.hpp"
#include "Figuras/Figuras.hpp"
#include "Figuras/Rectangulo.hpp"
#include "Figuras/Triangulo.hpp"

namespace CE {
    class Escena;
}

namespace IVJ {
    class Juego: public CE::GameLayer {
        public:
        explicit Juego();
        void OnInit();
        void OnInputs(float dt,
            std::optional<sf::Event>& eventos);
        void OnUpdate(float dt);
        void OnRender(float dt);
    private:
        CE::Escena* escena_actual;
        std::vector<std::shared_ptr<CE::Objeto>> figuras;

        std::vector<std::shared_ptr<Rectangulo>> rectangulos;
        std::vector<std::shared_ptr<Circulo>> circulos;
        std::vector<std::shared_ptr<Triangulo>> triangulos;
        //std::vector<std::shared_ptr<CE::Objeto>> figuras;
    };
}
