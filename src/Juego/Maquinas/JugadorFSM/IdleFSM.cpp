#include "IdleFSM.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MoverFSM.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

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
        // Obtener sprite
        auto c_sprite = obj.getComponente<CE::ISprite>();
        sprite = &c_sprite->m_sprite;

        s_w = c_sprite->width;
        s_h = c_sprite->height;

        // ============================
        // Cargar JSON (solo 2 frames)
        // ============================
        json j;
        try {
            std::ifstream file(ASSETS "/sprites/ElRenacido/idle.json");
            file >> j;
        }
        catch (...) {
            std::cout << "[IdleFSM] ERROR leyendo idle.json\n";
            return;
        }

        int i = 0;
        for (auto& kv : j["frames"].items())
        {
            auto& f = kv.value()["frame"];

            ani_frames[i] = {
                (float)f["x"],
                (float)f["y"]
            };

            s_w = (int)f["w"];
            s_h = (int)f["h"];

            i++;
            if (i >= 4) break; // Solo 4 frames
        }

        id_actual = 0;
        max_tiempo = 0.4f;  // 4 FPS por ejemplo
        tiempo = max_tiempo;
    }

    void IdleFSM::onSalir(const Entidad& obj)
    {
        // Nada por ahora
    }

    void IdleFSM::onUpdate(const Entidad& obj, float dt)
    {
        tiempo -= dt;

        if (tiempo <= 0)
        {
            auto& f = ani_frames[id_actual % 2];

            sprite->setTextureRect(
        sf::IntRect(
            sf::Vector2i( (int)f.x, (int)f.y ),
            sf::Vector2i( s_w, s_h )
        )
    );

            id_actual++;
            tiempo = max_tiempo;
        }
    }
}
