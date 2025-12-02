#include "AgacharseFSM.hpp"
#include "IdleFSM.hpp"
#include "MoverFSM.hpp"
#include <iostream>

namespace IVJ
{
    AgacharseFSM::AgacharseFSM(bool flipsprite)
        : FSM{}, flip{flipsprite}, totalmente_agachado{true}  // Cambiado a true
    {
        nombre = "AgacharseFSM";
        std::cout << nombre << "\n";
    }

    FSM* AgacharseFSM::onInputs(const CE::IControl& control)
    {
        // Si suelta la tecla de agacharse
        if (!control.abj)
        {
            // Verificar si debe moverse o estar idle
            if (control.der)
                return new MoverFSM(flip);  // Usar la dirección actual (flip)
            else if (control.izq)
                return new MoverFSM(flip);  // Usar la dirección actual (flip)
            else
                return new IdleFSM();
        }

        // Permitir movimiento mientras está agachado
        // Solo crear nuevo estado si cambia la dirección
        if (control.der && flip)  // Quiere ir a la derecha pero está mirando izquierda
            return new AgacharseFSM(false);  // Cambiar a mirar derecha
        else if (control.izq && !flip)  // Quiere ir a la izquierda pero está mirando derecha
            return new AgacharseFSM(true);   // Cambiar a mirar izquierda

        return nullptr;
    }

    void AgacharseFSM::onEntrar(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();
        sprite = &csprite->m_sprite;
        s_w = 64;
        s_h = 64;

        ani_frames[0] = {256.f, 256.f};

        max_tiempo = 0.15f;
        tiempo = max_tiempo;
        id_actual = 0;
        totalmente_agachado = true;

        if (obj.tieneComponente<CE::IBoundingBox>())
        {
            auto bbox = obj.getComponente<CE::IBoundingBox>();
            bbox_original = bbox->tam;
        }

        // Aplicar frame
                sprite->setTextureRect(
             sf::IntRect(
                 sf::Vector2i(static_cast<int>(ani_frames[0].x), static_cast<int>(ani_frames[0].y)),
                 sf::Vector2i(s_w, s_h)
             )
         );

        ajustarBoundingBox(obj, true);

        auto trans = const_cast<Entidad&>(obj).getTransformada();
        trans->posicion.y = 970.f;
    }


    void AgacharseFSM::flipSprite(const Entidad& obj)
    {
        auto csprite = obj.getComponente<CE::ISprite>();

        if (flip)
            sprite->setScale({ -csprite->escala, csprite->escala });
        else
            sprite->setScale({ csprite->escala, csprite->escala });
    }

    void AgacharseFSM::ajustarBoundingBox(const Entidad& obj, bool agachado)
    {
        auto& obj_mutable = const_cast<Entidad&>(obj);
        auto bbox = obj_mutable.getComponente<CE::IBoundingBox>();

        if (agachado)
        {
            // Reducir altura del bounding box a la mitad
            bbox->tam.y = bbox_original.y * 0.5f;
            bbox->mitad.y = bbox->tam.y / 2.f;
        }
        else
        {
            // Restaurar bounding box original
            bbox->tam = bbox_original;
            bbox->mitad.x = bbox->tam.x / 2.f;
            bbox->mitad.y = bbox->tam.y / 2.f;
        }
    }


    void AgacharseFSM::onSalir(const Entidad& obj)
    {
        // Restaurar bounding box al salir
        ajustarBoundingBox(obj, false);
    }

    void AgacharseFSM::onUpdate(Entidad& obj, float dt)
    {
        // Permitir movimiento horizontal más lento mientras está agachado
        auto trans = obj.getTransformada();
        float velocidad_agachado = 30.0f;  // La mitad de velocidad que MoverFSM (60 -> 30)

        // Solo mover si el jugador está presionando una tecla de movimiento
        // Necesitaríamos acceso al control aquí, pero podemos usar un enfoque diferente

        // Mantener el frame de agachado
        sprite->setTextureRect(
            sf::IntRect{
                {
                    static_cast<int>(ani_frames[0].x),
                    static_cast<int>(ani_frames[0].y)
                },
                {
                    s_w,
                    s_h
                }
            }
        );

        // Bloquear movimiento vertical
        trans->velocidad.y = 0;
    }
}