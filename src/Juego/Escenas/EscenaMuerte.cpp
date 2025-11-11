#include "EscenaMuerte.hpp"
#include "../Figuras/Figura.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../Sistema/Sistema.hpp"
#include <Motor/Primitivos/GestorEscenas.hpp>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <thread>

namespace IVJ {

void EscenaMuerte::onInit() {
    if (!inicializar) {
        CE::GestorCamaras::Get().setCamaraActiva(2);
        return;
    }

    srand(time(0)); // Seed the random number generator

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

    // 🔹 Crear figuras con vida inicial
    for (int i = 0; i < 50; i++) {
        int xr = 50 + rand() % 900;
        int yr = 50 + rand() % 650;
        auto fig1 = std::make_shared<Rectangulo>(
            100, 100, 500.f, 700.f, sf::Color(0, 255, 0, 255), sf::Color(0, 0, 0, 255));
        fig1->setPosicion(xr, yr);
        fig1->getStats()->hp = 100;
        objetos.agregarPool(fig1);
    }

    // 🔹 Cámara
    CE::GestorCamaras::Get().agregarCamara(
        std::make_shared<CE::CamaraAreaBox>(
            CE::Vector2D{540, 360}, CE::Vector2D{1080.f, 720.f}));
    CE::GestorCamaras::Get().setCamaraActiva(2);
    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(objetos[6]);

    inicializar = false;
}

void EscenaMuerte::onFinal() { }

void EscenaMuerte::onUpdate(float dt) {
    SistemaMovimientoEntes(objetos.getPool(), dt);

    for (auto& f : objetos.getPool()) {
        f->onUpdate(dt);
        f->getStats()->hp -= rand() % 20;

        int hp = f->getStats()->hp;
        sf::Color nuevoColor;


        // 🔹 Seleccionar color según la vida
        if (hp >= 80) {
            nuevoColor = sf::Color(0, 255, 0); // Verde
        } else if (hp <= 70 && hp >= 40) {
            nuevoColor = sf::Color(255, 255, 0); // Amarillo
        } else if (hp <= 30) {
            nuevoColor = sf::Color(255, 0, 0); // Rojo
        } else {
            nuevoColor = sf::Color(255, 255, 255); // Por si cae en un rango intermedio
        }

        // 🔹 Aplicar el color según el tipo de figura
        if (auto rect = std::dynamic_pointer_cast<Rectangulo>(f)) {
            rect->c_relleno = nuevoColor;
            rect->imagen.setFillColor(nuevoColor);
        }
        else if (auto circ = std::dynamic_pointer_cast<Circulo>(f)) {
            circ->c_relleno = nuevoColor;
            circ->imagen.setFillColor(nuevoColor);
        }
        else if (auto tri = std::dynamic_pointer_cast<Triangulo>(f)) {
            tri->c_relleno = nuevoColor;
            tri->imagen.setFillColor(nuevoColor);
        }

        // 🔹 Controlar que no baje de 0
        if (hp <= 0)
            f->getStats()->hp = 0;
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(50));

    if (objetos.getPool().empty()) {
        CE::GestorEscenas::Get().cambiarEscena("Cuadros");
    }

    objetos.borrarPool();
}

void EscenaMuerte::onInputs(const CE::Botones& accion) {
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

void EscenaMuerte::onRender() {
    for (auto& f : objetos.getPool())
        CE::Render::Get().AddToDraw(*f);
}

}
