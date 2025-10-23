#pragma once
#include <Motor/App/ALayer.hpp> // contiene GameLayer
#include <optional>
#include <SFML/Graphics.hpp>

namespace IVJ
{
    class Juego : public CE::GameLayer
    {
    public:
        explicit Juego();

        void OnInit(void) override;
        void OnInputs(float dt, std::optional<sf::Event>& eventos) override;
        void OnUpdate(float dt) override;
        void OnRender(float dt) override;

    private:
        // Ejemplo: un círculo que puedes mover/dibujar
        sf::CircleShape circle;
    };
}
