#pragma once
#include "../FSM.hpp"
#include <SFML/Graphics.hpp>

namespace IVJ
{
    class CorrerFSM : public FSM
    {
    public:
        CorrerFSM(bool flipsprite);
        ~CorrerFSM() override = default;

        FSM* onInputs(const CE::IControl& control) override;
        void onEntrar(const Entidad& obj) override;
        void onSalir(const Entidad& obj) override;
        void onUpdate(Entidad& obj, float dt) override;

    private:
        void flipSprite(const Entidad& obj);

        sf::Sprite* sprite;
        sf::Vector2f ani_frames[6];  // frames de animación de correr

        int s_w;        // ancho del sprite
        int s_h;        // alto del sprite
        float max_tiempo;
        float tiempo;
        int id_actual;
        bool flip;      // dirección del sprite
    };
}