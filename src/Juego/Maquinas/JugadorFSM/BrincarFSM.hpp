#pragma once
#include "../FSM.hpp"
#include <SFML/Graphics.hpp>

#include "Juego/objetos/Entidad.hpp"

namespace IVJ
{
    class BrincarFSM : public FSM
    {
    public:
        BrincarFSM(bool flipsprite);
        ~BrincarFSM() override = default;

        FSM* onInputs(const CE::IControl& control) override;
        void onEntrar(const Entidad& obj) override;
        void onSalir(const Entidad& obj) override;
        void onUpdate(const Entidad& obj, float dt) override;

    private:
        void flipSprite(const Entidad& obj);

        sf::Sprite* sprite;
        sf::Vector2f ani_frames[8];  // 8 frames de animación de salto

        int s_w;        // ancho del sprite
        int s_h;        // alto del sprite
        float max_tiempo;
        float tiempo;
        int id_actual;
        bool flip;      // dirección del sprite

        // Control de física del salto
        float velocidad_salto;
        float velocidad_horizontal;  // velocidad en X durante el salto
        float gravedad;
        bool en_aire;
    };
}
