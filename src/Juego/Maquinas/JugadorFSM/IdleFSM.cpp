#include "IdleFSM.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
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
        if (control.arr)
            return new MoverFSM(false);
        else if (control.abj)
            return new MoverFSM(true);
        else if (control.der)
            return new MoverFSM(false);
        else if (control.izq)
            return new MoverFSM(true);
        return nullptr;
    }

    void IdleFSM::onEntrar(const Entidad& obj)
    {
        // Obtener componente Sprite
        auto c_sprite = obj.getComponente<CE::ISprite>();
        sprite = &c_sprite->m_sprite;

        s_w = c_sprite->width;
        s_h = c_sprite->height;

        // Frames de animación
        ani_frames[0] = {0.f, 193.f};
        ani_frames[1] = {0.f,  96.f};

        max_tiempo = 0.2f;   // 5 FPS
        tiempo = max_tiempo;
        id_actual = 0;
    }

    void IdleFSM::onSalir(const Entidad& obj){}// Nada por el momento//

    void IdleFSM::onUpdate(const Entidad &obj, float dt)
    {
        //el framerate de la animacion
        tiempo=tiempo-1*dt;
        if (tiempo<=0)
        {
            //mover el cuadro
            sprite->setTextureRect(
                sf::IntRect{
                    {//posicion
                        (int) ani_frames[id_actual%2].x,
                        (int)ani_frames[id_actual%2].y
                    },
                    {//tamaño
                        s_w,
                        s_h

                }});
            tiempo=max_tiempo;
            id_actual++;
        }
    }

}

