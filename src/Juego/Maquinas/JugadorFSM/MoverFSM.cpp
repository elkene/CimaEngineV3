#include "MoverFSM.hpp"
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
        // si deja de moverse -> volver a Idle
        if (!control.arr && !control.abj && !control.der && !control.izq)
            return new IdleFSM();

        // si presiona derecha → ver derecha
        if (control.der)
        {
            if (flip != false)   // solo cambia si realmente cambia la dirección
                flip = false;
        }
        // si presiona izquierda → rotar (flip X)
        else if (control.izq)
        {
            if (flip != true)
                flip = true;
        }

        return nullptr;
    }

    void MoverFSM::onEntrar(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();
        sprite = &csprite->m_sprite;
        s_w = csprite->width;
        s_h = csprite->height;

        ani_frames[0] = {0.f, 6.f};
        ani_frames[1] = {32.f, 75.f};
        ani_frames[2] = {64.f, 90.f};
        ani_frames[3] = {96.f, 105.f};

        max_tiempo = 0.6f;
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

        // solo cambiar flip si la dirección cambió en onInputs()
        flipSprite(obj);

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
