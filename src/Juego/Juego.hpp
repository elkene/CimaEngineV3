#pragma once
#include <Motor/App/ALayer.hpp>
#include "Figuras/Figura.hpp"
#include <memory>
#include <vector>

namespace IVJ
{
    class Juego : public CE::GameLayer
    {
        public:
            explicit Juego();
            void OnInit(void);
            void OnInputs(float,std::optional<sf::Event>& eventos);
            void OnUpdate(float dt);
            void OnRender(float dt);
        private:
            std::vector<std::shared_ptr<CE::Objeto>> objetos;
            sf::Font font_juego;
            sf::Text texto;
    };
}
