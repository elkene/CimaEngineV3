// EnemigoSeguirFSM.hpp corregido
#pragma once
#include "../FSM.hpp"
#include "Motor/Utils/Lerp.hpp"
#include <memory>

namespace IVJ
{
    class EnemigoSeguirFSM : public FSM
    {
    private:
        bool flip; // Dirección en la que mira el enemigo
        float velocidad_seguimiento;
        std::shared_ptr<Entidad> objetivo;

        // Variables para Lerp/interpolación
        CE::Vector2D posicion_inicial;
        CE::Vector2D posicion_objetivo;
        float tiempo_transcurrido;
        float tiempo_total_interpolacion;
        float velocidad;

    public:
        EnemigoSeguirFSM(bool flipsprite, std::shared_ptr<Entidad> jugador, float velocidad_seguimiento = 100.0f);
        FSM* onInputs(const CE::IControl& control) override;
        void onEntrar(const Entidad& obj) override;
        void onSalir(const Entidad& obj) override;
        void onUpdate(Entidad& obj, float dt) override;

    private:
        void seguirJugador(Entidad& obj);
        void actualizarDireccion(const Entidad& obj);
    };
}