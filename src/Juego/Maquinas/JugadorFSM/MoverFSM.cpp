#include "MoverFSM.hpp"

#include "BrincarFSM.hpp"
#include "IdleFSM.hpp"
#include "AgacharseFSM.hpp"
namespace IVJ
{

    MoverFSM::MoverFSM(bool flipsprite)
        : FSM{}, flip{flipsprite}
    {
        nombre = "MoverFSM";
        std::cout << nombre << "\n";
    }

    FSM* MoverFSM::onInputs(const CE::IControl& control)
    {
        if (control.saltar)
            return new BrincarFSM(flip);

        if (control.abj)  // <-- AGREGAR ESTO
            return new AgacharseFSM(flip);

        // si deja de moverse -> volver a Idle
        if (!control.der && !control.izq)
            return new IdleFSM();

        return nullptr;
    }

    void MoverFSM::onEntrar(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();
        sprite = &csprite->m_sprite;
        s_w = 64;
        s_h = 64;

        ani_frames[0] = {0.f, 130.f};
        ani_frames[1] = {64.f, 130.f};
        ani_frames[2] = {128.f, 130.f};
        ani_frames[3] = {192.f, 130.f};

        max_tiempo = 0.3f;
        tiempo = max_tiempo;
        id_actual = 0;

        flipSprite(obj);   // aplicar flip inicial
    }

    void MoverFSM::flipSprite(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();

        if (flip)
            sprite->setScale({ -csprite->escala, csprite->escala }); // volteado
        else
            sprite->setScale({ csprite->escala, csprite->escala });  // normal
    }

    void MoverFSM::onSalir(const Entidad& obj)
    {
    }

    void MoverFSM::onUpdate(Entidad& obj, float dt)
    {
        // ------------------------------------
        // 1. Mover al OBJETO, NO al sprite
        // ------------------------------------
        float velocidad = 200.f;  // píxeles por segundo (ajusta a tu juego)

        auto pos = obj.getTransformada()->posicion;

        if (flip)
            pos.x -= velocidad * dt;   // mover hacia la izquierda
        else
            pos.x += velocidad * dt;   // mover hacia la derecha

        obj.setPosicion(pos.x, pos.y);

        // ------------------------------------
        // 2. Animación (igual que antes)
        // ------------------------------------
        tiempo -= dt;

        if (tiempo <= 0)
        {
            sprite->setTextureRect(
                sf::IntRect{
                    {
                        static_cast<int>(ani_frames[id_actual % 4].x),
                        static_cast<int>(ani_frames[id_actual % 4].y)
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
