#include "BrincarFSM.hpp"
#include "IdleFSM.hpp"
#include "MoverFSM.hpp"
#include <iostream>

namespace IVJ
{
    BrincarFSM::BrincarFSM(bool flipsprite)
        : FSM{}, flip{flipsprite}, en_aire{true}
    {
        nombre = "BrincarFSM";
        std::cout << nombre << "\n";

        velocidad_salto = 0.5f;
        gravedad = 400.f;  // gravedad en píxeles/s²
    }

    FSM* BrincarFSM::onInputs(const CE::IControl& control)
    {
        // Si ya no está en el aire (terminó el salto)
        if (!en_aire)
        {
            // Verificar si debe moverse o estar idle
            if (control.der)
                return new MoverFSM(false);
            else if (control.izq)
                return new MoverFSM(true);
            else
                return new IdleFSM();
        }

        return nullptr;
    }

    void BrincarFSM::onEntrar(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();
        sprite = &csprite->m_sprite;
        s_w = 64;
        s_h = 64;

        // Frames de animación de salto (ajusta según tu spritesheet)
        ani_frames[0] = {0.f, 320.f};   // inicio del salto
        ani_frames[1] = {64.f, 320.f};  // subiendo
        ani_frames[2] = {128.f, 320.f}; // en el aire
        ani_frames[3] = {192.f, 320.f}; // cayendo
        ani_frames[4] = {256.f, 320.f}; // cayendo
        ani_frames[5] = {320.f, 320.f}; // cayendo
        ani_frames[6] = {384.f, 320.f}; // cayendo
        ani_frames[7] = {448.f, 320.f}; // cayendo


        max_tiempo = 0.3f;  // velocidad de animación
        tiempo = max_tiempo;
        id_actual = 0;

        // Inicializar física del salto
        velocidad_salto = -400.f;  // velocidad inicial hacia arriba (negativa)
        en_aire = true;

        flipSprite(obj);  // aplicar dirección
    }

    void BrincarFSM::flipSprite(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();

        if (flip)
            sprite->setScale({ -csprite->escala, csprite->escala });
        else
            sprite->setScale({ csprite->escala, csprite->escala });
    }

    void BrincarFSM::onSalir(const Entidad& obj)
    {
        // Restaurar posición si es necesario
        en_aire = false;
    }

    void BrincarFSM::onUpdate(Entidad& obj, float dt)
    {
        // Actualizar física del salto
        velocidad_salto += gravedad * dt;

        // Mover el sprite verticalmente
        auto pos = obj.getTransformada()->posicion;
        float nueva_y = pos.y + velocidad_salto * dt;
        obj.setPosicion(pos.x, nueva_y);  // Mantener X, solo cambiar Y

        // Verificar si llegó al suelo (ajusta según tu juego)
        // Aquí asumimos que y = 400 es el suelo
        if (obj.getTransformada()->posicion.y >= 970.f)
        {
            auto pos = obj.getTransformada()->posicion;
            obj.setPosicion(pos.x,970.f);

            en_aire = false;
            velocidad_salto = 2.f;
        }

        // Actualizar animación
        tiempo -= dt;

        if (tiempo <= 0)
        {
            // Seleccionar frame según la fase del salto
            int frame_index;
            if (velocidad_salto < -200.f)
                frame_index = 0;  // subiendo rápido
            else if (velocidad_salto < 0.f)
                frame_index = 1;  // subiendo lento
            else if (velocidad_salto < 200.f)
                frame_index = 2;  // cayendo lento
            else
                frame_index = 3;  // cayendo rápido

            sprite->setTextureRect(
                sf::IntRect{
                    {
                        static_cast<int>(ani_frames[frame_index].x),
                        static_cast<int>(ani_frames[frame_index].y)
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