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
        if (!control.arr && !control.abj && !control.der && !control.izq)
            return new IdleFSM();

        if (control.der)
            flip = false;
        else if (control.izq)
            flip = true;

        return nullptr;
    }

    void MoverFSM::onEntrar(const Entidad& obj)
    {
        // podemos acceder al sprite desde obj
        auto csprite = obj.getComponente<CE::ISprite>();
        sprite = &csprite->m_sprite;
        s_w = csprite->width;
        s_h = csprite->height;

        // los valores siguientes son el spritesheet del alien pink
        // frame walk 1 y 2
        ani_frames[0] = { 69.f, 193.f };
        ani_frames[1] = {  0.f,   0.f };

        max_tiempo = 0.4f; // en segundos
        tiempo = max_tiempo; // timer
        id_actual = 0;

        // flip
        flipSprite(obj);
    }

    void MoverFSM::flipSprite(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();

        if (flip)
            sprite->setScale({ -csprite->escala, csprite->escala });
        else
            sprite->setScale({ csprite->escala, csprite->escala });
    }

    void MoverFSM::onSalir(const Entidad& obj)
    {
    }

    void MoverFSM::onUpdate(const Entidad& obj, float dt)
    {
        // frame rate de la animación
        tiempo = tiempo - 1 * dt;

        flipSprite(obj);

        if (tiempo <= 0)
        {
            // mover el cuadro
            sprite->setTextureRect(
                sf::IntRect{
                    {
                        (int)ani_frames[id_actual % 2].x,
                        (int)ani_frames[id_actual % 2].y
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

} // namespace IVJ
