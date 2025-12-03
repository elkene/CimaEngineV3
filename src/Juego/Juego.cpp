#include "Juego.hpp"
#include "Juego/Escenas/EscenaCuadro.hpp"
#include "Juego/Escenas/EscenaCirculo.hpp"
#include "Juego/Escenas/EscenaMuerte.hpp"
#include "Motor/Primitivos/GestorEscenas.hpp"
#include <iostream>

#include "Escenas/EscenaLerp.hpp"

namespace IVJ {

    Juego::Juego()
        : escenaActual(nullptr)
    {
        std::cout << "Constructor de Juego llamado\n";
    }

    void Juego::OnInit(void) {
        std::cout << "Inicializando Juego\n";

        // 🔹 Registrar las escenas
        //CE::GestorEscenas::Get().registrarEscena("Lerp", std::make_shared<EscenaLerp>());
        CE::GestorEscenas::Get().registrarEscena("Cuadros", std::make_shared<EscenaCuadros>());
        //CE::GestorEscenas::Get().registrarEscena("Circulos", std::make_shared<EscenaCirculos>());
        //CE::GestorEscenas::Get().registrarEscena("Muerte", std::make_shared<EscenaMuerte>());


        // 🔹 Escena inicial
        CE::GestorEscenas::Get().cambiarEscena("Cuadros");
        escenaActual = &CE::GestorEscenas::Get().getEscenaActual();
    }

    void Juego::OnInputs(float dt, std::optional<sf::Event>& eventos) {
        if (!eventos.has_value())
            return;

        const auto& ev = eventos.value();

        // 🔹 Si la ventana se cierra
        if (ev.is<sf::Event::Closed>()) {
            termino = true;
            return;
        }

        CE::Botones::TipoAccion tipoAccion = CE::Botones::TipoAccion::None;
        std::string strAccion = "None";
        sf::Keyboard::Scancode scan = sf::Keyboard::Scancode::Unknown;

        // 🔹 Presión de tecla
        if (ev.is<sf::Event::KeyPressed>()) {
            const auto* e = ev.getIf<sf::Event::KeyPressed>();
            tipoAccion = CE::Botones::TipoAccion::OnPress;
            if (e) scan = e->scancode;
        }
        // 🔹 Soltar tecla
        else if (ev.is<sf::Event::KeyReleased>()) {
            const auto* e = ev.getIf<sf::Event::KeyReleased>();
            tipoAccion = CE::Botones::TipoAccion::OnRelease;
            if (e) scan = e->scancode;
        }

        // 🔹 Si hay acción asociada
        if (scan != sf::Keyboard::Scancode::Unknown &&
            escenaActual->getBotones().count(scan))
        {
            strAccion = escenaActual->getBotones().at(scan);
            escenaActual->onInputs(CE::Botones(strAccion, tipoAccion, scan));
        }
    }

    void Juego::OnUpdate(float dt) {
        escenaActual = &CE::GestorEscenas::Get().getEscenaActual();
        escenaActual->onUpdate(dt);
    }

    void Juego::OnRender(float dt) {
        escenaActual->onRender();
    }

} // namespace IVJ
