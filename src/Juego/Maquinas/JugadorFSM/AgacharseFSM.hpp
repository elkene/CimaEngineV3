#pragma once
#include "../FSM.hpp"
#include <SFML/Graphics.hpp>

namespace IVJ
{
    class AgacharseFSM : public FSM
    {
    public:
        AgacharseFSM(bool flipsprite);
        ~AgacharseFSM() override = default;

        FSM* onInputs(const CE::IControl& control) override;
        void onEntrar(const Entidad& obj) override;
        void onSalir(const Entidad& obj) override;
        void onUpdate(Entidad &obj, float dt);

    private:
        void flipSprite(const Entidad& obj);
        void ajustarBoundingBox(const Entidad& obj, bool agachado);

        sf::Sprite* sprite;
        sf::Vector2f ani_frames[6];  // frames de animación de agacharse

        int s_w;        // ancho del sprite
        int s_h;        // alto del sprite
        float max_tiempo;
        float tiempo;
        int id_actual;
        bool flip;      // dirección del sprite
        bool totalmente_agachado;  // indica si completó la animación de agacharse

        // Guardar bounding box original
        CE::Vector2D bbox_original;
    };
}