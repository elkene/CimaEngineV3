#include "EscenaCirculo.hpp"
#include "../Figuras/Figura.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../Sistema/Sistema.hpp"

namespace IVJ {

void EscenaCirculos::onInit() {
    if (!inicializar) return;

    // 🔹 Registrar controles
    registrarBotones(sf::Keyboard::Scan::W, "arriba");
    registrarBotones(sf::Keyboard::Scan::Up, "arriba");
    registrarBotones(sf::Keyboard::Scan::S, "abajo");
    registrarBotones(sf::Keyboard::Scan::Down, "abajo");
    registrarBotones(sf::Keyboard::Scan::A, "izquierda");
    registrarBotones(sf::Keyboard::Scan::Left, "izquierda");
    registrarBotones(sf::Keyboard::Scan::D, "derecha");
    registrarBotones(sf::Keyboard::Scan::Right, "derecha");
    registrarBotones(sf::Keyboard::Scan::Escape, "cuadros");

    // 🔹 Crear tres círculos
    auto fig1 = std::make_shared<Circulo>(
        100, 700.f,500.f,sf::Color(255, 0, 0, 255), sf::Color(0, 0, 0, 255));
    fig1->setPosicion(300, 400);
    fig1->getStats()->hp = 100;

    auto fig2 = std::make_shared<Circulo>(
        200,350.f,600.f, sf::Color(169, 169, 0, 255), sf::Color(0, 0, 0, 255));
    fig2->setPosicion(100, 100);
    fig2->getStats()->hp = 100;

    auto fig3 = std::make_shared<Circulo>(
        100, 200.f,400.f,sf::Color(0, 0, 255, 255), sf::Color(0, 0, 0, 255));
    fig3->setPosicion(300, 600);
    fig3->getStats()->hp = 100;

    // 🔹 Añadir los objetos
    objetos.agregarPool(fig1);
    objetos.agregarPool(fig2);
    objetos.agregarPool(fig3);

    // 🔹 La cámara sigue al segundo círculo
    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(objetos[1]);

    inicializar = false;
}

void EscenaCirculos::onFinal() { }

void EscenaCirculos::onUpdate(float dt) {
    SistemaMovimientoEntes(objetos.getPool(), dt);

    for (auto& f : objetos.getPool())
        f->onUpdate(dt);

    objetos.borrarPool();
}

void EscenaCirculos::onInputs(const CE::Botones& accion) {
    auto p = objetos[1]->getTransformada();

    if (accion.getTipo() == CE::Botones::TipoAccion::OnPress) {
        if (accion.getNombre() == "arriba")
            p->velocidad.y = -800;
        else if (accion.getNombre() == "derecha")
            p->velocidad.x = 800;
        else if (accion.getNombre() == "abajo")
            p->velocidad.y = 800;
        else if (accion.getNombre() == "izquierda")
            p->velocidad.x = -800;
        else if (accion.getNombre() == "cuadros")
            CE::GestorEscenas::Get().cambiarEscena("Cuadros");
    }
    else if (accion.getTipo() == CE::Botones::TipoAccion::OnRelease) {
        if (accion.getNombre() == "arriba" || accion.getNombre() == "abajo")
            p->velocidad.y = 0;
        else if (accion.getNombre() == "derecha" || accion.getNombre() == "izquierda")
            p->velocidad.x = 0;
    }
}

void EscenaCirculos::onRender() {
    for (auto& f : objetos.getPool())
        CE::Render::Get().AddToDraw(*f);
}

}
