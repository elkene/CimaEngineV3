#include "MoverFSM.hpp"
#include "IdleFSM.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

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
        std::cout << "[MoverFSM] Animación cargada con " << 4 << " frames\n";

        // obtener sprite
        auto csprite = obj.getComponente<CE::ISprite>();
        sprite = &csprite->m_sprite;
        s_w = csprite->width;
        s_h = csprite->height;

        // ============================
        // LEER JSON: mover.json
        // ============================
        json j;
        try
        {
            std::ifstream file(ASSETS"sprites/ElRenacido/caminar.json");
            file >> j;
        }
        catch (...)
        {
            std::cout << "[MoverFSM] ERROR cargando caminar.json\n";
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
        }
       auto total_frames = i; // guarda cuántos frames tiene la animación

        max_tiempo = 0.1f; // animación más rápida
        tiempo = max_tiempo;
        id_actual = 0;

        // aplicar flip
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
        // nada
    }

    void MoverFSM::onUpdate(const Entidad& obj, float dt)
    {
        tiempo -= dt;

        flipSprite(obj);

        if (tiempo <= 0)
        {
  std::cout << "[MoverFSM] Cambiando a frame " << id_actual << " at ("
              << f.x << ", " << f.y << ")\n";
            auto& f = ani_frames[id_actual % 4];

            sprite->setTextureRect(
                sf::IntRect(
                    sf::Vector2i((int)f.x, (int)f.y),
                    sf::Vector2i(s_w, s_h)
                )
            );

            tiempo = max_tiempo;
            id_actual++;
        }
    }

} // namespace IVJ
