// EnemigoSeguirFSM.cpp corregido
#include "EnemigoSeguirFSM.hpp"
#include <iostream>
#include <cmath>

namespace IVJ
{
    EnemigoSeguirFSM::EnemigoSeguirFSM(bool flipsprite, std::shared_ptr<Entidad> jugador, float velocidad_seguimiento)
      : FSM{}, flip{flipsprite}, objetivo{jugador}, velocidad{velocidad_seguimiento}
    {
        nombre = "EnemigoSeguirFSM";
        std::cout << nombre << "\n";
    }

    FSM* EnemigoSeguirFSM::onInputs(const CE::IControl& control)
    {
        return nullptr;
    }

    void EnemigoSeguirFSM::onEntrar(const Entidad& obj)
    {
        // Usar const_cast para obtener una referencia no-const temporalmente
        auto& obj_mutable = const_cast<Entidad&>(obj);

        // Guardar posición inicial
        posicion_inicial = CE::Vector2D{
            obj_mutable.getTransformada()->posicion.x,
            obj_mutable.getTransformada()->posicion.y
        };

        // Establecer posición objetivo inicial
        if (objetivo)
        {
            // Objetivo no es const en este contexto
            posicion_objetivo = CE::Vector2D{
                objetivo->getTransformada()->posicion.x,
                objetivo->getTransformada()->posicion.y
            };
        }
    }
    void EnemigoSeguirFSM::onSalir(const Entidad& obj)
    {
        // Limpieza
    }

    void EnemigoSeguirFSM::seguirJugador(Entidad& obj)
    {
        if (!objetivo) return;

        auto trans_enemigo = obj.getTransformada(); // No-const OK aquí
        auto trans_objetivo = objetivo->getTransformada(); // Const OK

        // Calcular dirección hacia el jugador
        float dx = trans_objetivo->posicion.x - trans_enemigo->posicion.x;
        float dy = trans_objetivo->posicion.y - trans_enemigo->posicion.y;

        // ... resto del código ...
    }

    void EnemigoSeguirFSM::actualizarDireccion(const Entidad& obj)
    {
        if (!objetivo) return;

        // Usar const_cast para obtener transformada del enemigo
        auto& obj_mutable = const_cast<Entidad&>(obj);
        auto trans_enemigo = obj_mutable.getTransformada();

        // Objetivo no es const en este contexto (es miembro de la clase)
        auto trans_objetivo = objetivo->getTransformada();

        // Actualizar dirección visual
        if (trans_objetivo->posicion.x > trans_enemigo->posicion.x)
            flip = true; // Mirar derecha
        else
            flip = false;  // Mirar izquierda

        // Aplicar flip al sprite
        if (obj.tieneComponente<CE::ISprite>())
        {
            // Usar la misma referencia mutable para el sprite
            auto& sprite = obj_mutable.getComponente<CE::ISprite>()->m_sprite;
            auto csprite = obj.getComponente<CE::ISprite>();

            if (flip)
                sprite.setScale({ -csprite->escala, csprite->escala });
            else
                sprite.setScale({ csprite->escala, csprite->escala });
        }
    }

    void EnemigoSeguirFSM::onUpdate(Entidad& obj, float dt)
    {
        if (!objetivo) return;

        auto trans = obj.getTransformada(); // No-const OK
        auto trans_objetivo = objetivo->getTransformada(); // Const OK

        // Calcular factor de interpolación
        float factor_lerp = velocidad * dt;

        // Interpolar posición usando método simple
        float dx = trans_objetivo->posicion.x - trans->posicion.x;
        float dy = trans_objetivo->posicion.y - trans->posicion.y;

        // Mover suavemente hacia el jugador
        float nueva_x = trans->posicion.x + dx * factor_lerp;
        float nueva_y = trans->posicion.y + dy * factor_lerp * 0.3f; // Más lento en Y

        // Actualizar posición
        obj.setPosicion(nueva_x, nueva_y);

        // Actualizar dirección
        if (dx > 5.0f)
            flip = true;
        else if (dx < -5.0f)
            flip = false;

        // Aplicar dirección al sprite
        if (obj.tieneComponente<CE::ISprite>())
        {
            auto& sprite = obj.getComponente<CE::ISprite>()->m_sprite;
            auto csprite = obj.getComponente<CE::ISprite>();

            if (flip)
                sprite.setScale({ -csprite->escala, csprite->escala });
            else
                sprite.setScale({ csprite->escala, csprite->escala });
        }
    }
}