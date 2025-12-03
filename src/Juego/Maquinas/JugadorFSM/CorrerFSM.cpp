#include "CorrerFSM.hpp"
#include "IdleFSM.hpp"
#include "MoverFSM.hpp"
#include "BrincarFSM.hpp"
#include "AgacharseFSM.hpp"
#include <iostream>

namespace IVJ
{
    CorrerFSM::CorrerFSM(bool flipsprite)
        : FSM{}, flip{flipsprite}
    {
        nombre = "CorrerFSM";
        std::cout << nombre << "\n";
    }

    FSM* CorrerFSM::onInputs(const CE::IControl& control)
    {
        // Si salta mientras corre
        if (control.saltar)
            return new BrincarFSM(flip);

        // Si se agacha mientras corre
        if (control.abj)
            return new AgacharseFSM(flip);

        // Si suelta shift pero sigue moviéndose -> caminar
        if (!control.correr && (control.der || control.izq))
            return new MoverFSM(flip);

        // Si deja de moverse o suelta shift -> idle
        if (!control.der && !control.izq)
            return new IdleFSM();

        return nullptr;
    }

    void CorrerFSM::onEntrar(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();
        sprite = &csprite->m_sprite;
        s_w = 64;
        s_h = 64;

        // Frames de animación de correr (ajusta según tu spritesheet)
        ani_frames[0] = {0.f, 194.f};     // frame 1
        ani_frames[1] = {64.f, 194.f};    // frame 2
        ani_frames[2] = {128.f, 194.f};   // frame 3
        ani_frames[3] = {192.f, 194.f};   // frame 4
        ani_frames[4] = {256.f, 194.f};   // frame 5
        ani_frames[5] = {320.f, 194.f};   // frame 6

        max_tiempo = 0.08f;  // animación más rápida que caminar
        tiempo = max_tiempo;
        id_actual = 0;

        flipSprite(obj);  // aplicar dirección
    }

    void CorrerFSM::flipSprite(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();

        if (flip)
            sprite->setScale({ -csprite->escala, csprite->escala }); // volteado
        else
            sprite->setScale({ csprite->escala, csprite->escala });  // normal
    }

    void CorrerFSM::onSalir(const Entidad& obj)
    {
        // Restaurar velocidad normal al salir
        auto trans = const_cast<Entidad&>(obj).getTransformada();
        if (trans->velocidad.x > 0)
            trans->velocidad.x = 60;  // velocidad normal
        else if (trans->velocidad.x < 0)
            trans->velocidad.x = -60;
    }

    void CorrerFSM::onUpdate(Entidad& obj, float dt)
    {
        // Actualizar velocidad de correr (más rápido que caminar)
        auto trans = obj.getTransformada();

        if (flip)
            trans->velocidad.x = -120;  // correr a la izquierda (doble de velocidad)
        else
            trans->velocidad.x = 120;   // correr a la derecha (doble de velocidad)

        // Actualizar animación
        tiempo -= dt;

        if (tiempo <= 0)
        {
            // Actualizar frame
            sprite->setTextureRect(
                sf::IntRect{
                    {
                        static_cast<int>(ani_frames[id_actual % 6].x),
                        static_cast<int>(ani_frames[id_actual % 6].y)
                    },
                    {
                        s_w,
                        s_h
                    }
                }
            );

            tiempo = max_tiempo;
            id_actual++;
        }
    }
}