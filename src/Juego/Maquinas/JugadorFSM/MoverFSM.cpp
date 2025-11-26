#include "MoverFSM.hpp"

#include "BrincarFSM.hpp"
#include "IdleFSM.hpp"

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
            return new BrincarFSM(flip);  // Mantiene la dirección actual

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

    void MoverFSM::onUpdate(const Entidad& obj, float dt)
    {
        tiempo -= dt;


        if (tiempo <= 0)
        {
            // actualizar frame
            sprite->setTextureRect(
                sf::IntRect{
                    {   // posición
                        static_cast<int>(ani_frames[id_actual % 4].x),
                        static_cast<int>(ani_frames[id_actual % 4].y)
                    },
                    {   // tamaño
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
