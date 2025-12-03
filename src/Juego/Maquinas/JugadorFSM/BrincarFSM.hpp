#pragma once
#include "../FSM.hpp"
#include "Motor/Componentes/IComponentes.hpp"
#include <vector>
#include <memory>

namespace IVJ
{
    class BrincarFSM : public FSM
    {
    public:
        BrincarFSM(bool flipsprite = false);
        virtual ~BrincarFSM() = default;

        FSM* onInputs(const CE::IControl& control) override;
        void onEntrar(const Entidad& obj) override;
        void onSalir(const Entidad& obj) override;
        void onUpdate(Entidad& obj, float dt) override;
        void flipSprite(const Entidad& obj);

        // Método para verificar colisiones con objetos
        bool verificarColisionSuelo(Entidad& jugador, const std::vector<std::shared_ptr<CE::Objeto>>& objetos);

        // Setter para marcar cuando aterrizó
        void setAterrizo(bool valor) { en_aire = !valor; }

    private:
        bool flip;
        bool en_aire;
        float velocidad_salto;
        float gravedad;

        // Animación
        sf::Sprite* sprite;
        int s_w, s_h;
        CE::Vector2D ani_frames[8];
        float max_tiempo;
        float tiempo;
        int id_actual;
    };
}