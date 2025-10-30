#include "EscenaCuadro.hpp"
#include "../Figuras/Figura.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../Sistema/Sistema.hpp"

namespace IVJ {

void EscenaCuadros::onInit() {
    if (!inicializar) {
        CE::GestorCamaras::Get().setCamaraActiva(1);
        return;
    }

    // 🔹 Registro de controles
    registrarBotones(sf::Keyboard::Scan::W, "arriba");
    registrarBotones(sf::Keyboard::Scan::Up, "arriba");
    registrarBotones(sf::Keyboard::Scan::S, "abajo");
    registrarBotones(sf::Keyboard::Scan::Down, "abajo");
    registrarBotones(sf::Keyboard::Scan::A, "izquierda");
    registrarBotones(sf::Keyboard::Scan::Left, "izquierda");
    registrarBotones(sf::Keyboard::Scan::D, "derecha");
    registrarBotones(sf::Keyboard::Scan::Right, "derecha");
    registrarBotones(sf::Keyboard::Scan::Escape, "circulos");

    // 🔹 Creación de tres figuras rectangulares
    auto fig1 = std::make_shared<Rectangulo>(
        100, 100,500.f,700.f ,sf::Color(255, 0, 0, 255), sf::Color(0, 0, 0, 255));
    fig1->getStats()->hp = 100;

    auto fig2 = std::make_shared<Rectangulo>(
        200, 100, 350.f,400.f,sf::Color(169, 169, 0, 255), sf::Color(0, 0, 0, 255));
    fig2->getStats()->hp = 100;

    auto fig3 = std::make_shared<Rectangulo>(
        100, 200,100.f,200.f ,sf::Color(0, 0, 255, 255), sf::Color(0, 0, 0, 255));
    fig3->getStats()->hp = 100;

    // 🔹 Añadimos las figuras al pool de objetos
    objetos.agregarPool(fig1);
    objetos.agregarPool(fig2);
    objetos.agregarPool(fig3);

    // 🔹 Cámara
    CE::GestorCamaras::Get().agregarCamara(
        std::make_shared<CE::CamaraCuadro>(
            CE::Vector2D{540, 360}, CE::Vector2D{1080.f, 720.f}));
    CE::GestorCamaras::Get().setCamaraActiva(1);

    // La cámara sigue al objeto 2
    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(objetos[1]);

    inicializar = false;
}

void EscenaCuadros::onFinal() { }

void EscenaCuadros::onUpdate(float dt) {
    SistemaMovimientoEntes(objetos.getPool(), dt);

    for (auto& f : objetos.getPool())
        f->onUpdate(dt);

    objetos.borrarPool();
}

void EscenaCuadros::onInputs(const CE::Botones& accion) {
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
        else if (accion.getNombre() == "circulos")
            CE::GestorEscenas::Get().cambiarEscena("Circulos");
    }
    else if (accion.getTipo() == CE::Botones::TipoAccion::OnRelease) {
        if (accion.getNombre() == "arriba" || accion.getNombre() == "abajo")
            p->velocidad.y = 0;
        else if (accion.getNombre() == "derecha" || accion.getNombre() == "izquierda")
            p->velocidad.x = 0;
    }
}

void EscenaCuadros::onRender() {
    for (auto& f : objetos.getPool())
        CE::Render::Get().AddToDraw(*f);
}

}
