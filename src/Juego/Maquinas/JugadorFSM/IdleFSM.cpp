#include "IdleFSM.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "BrincarFSM.hpp"
#include "MoverFSM.hpp"

namespace IVJ
{

    IdleFSM::IdleFSM()
        : FSM{}
    {
        nombre = "IdleFSM";
        std::cout << nombre << "\n";
    }
    FSM* IdleFSM::onInputs(const CE::IControl& control)
    {
        if (control.saltar) {
            // Determinar dirección basada en el último input
            bool saltarIzquierda = control.izq;
            return new BrincarFSM(saltarIzquierda);
        }
        else if (control.der)
            return new MoverFSM(false);
        else if (control.izq)
            return new MoverFSM(true);

        return nullptr;
    }

    void IdleFSM::onEntrar(const Entidad& obj)
    {
        // podemos acceder al sprite desde obj
        auto csprite = obj.getComponente<CE::ISprite>();
        sprite = &csprite->m_sprite;
        s_w = csprite->width;
        s_h = csprite->height;

        // swimn 1 y 2
        ani_frames[0] = {4.f, 2.f};
        ani_frames[1] = {68.f, 2.f};

        max_tiempo = 0.4f;  // frame rate en segundos
        tiempo = max_tiempo;
        id_actual = 0;
    }

    void IdleFSM::onSalir(const Entidad& obj)
    {
    }

    void IdleFSM::onUpdate(Entidad& obj, float dt)
    {
        // frame rate de la animación
        tiempo -= 1 * dt;

        if (tiempo <= 0)
        {
            // mover el cuadro
            sprite->setTextureRect(
                sf::IntRect{
                    {   // posición
                        (int)ani_frames[id_actual % 2].x,
                        (int)ani_frames[id_actual % 2].y
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
