#include "EscenaLerp.hpp"
#include "../Figuras/Figura.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../Sistema/Sistema.hpp"
#include "../../Motor/Utils/Lerp.hpp"

namespace IVJ {

void EscenaLerp::onInit() {
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

    // 🔹 Creación de tres figuras rectangulares
    auto fig1 = std::make_shared<Rectangulo>(
        100, 100,500.f,200.f ,sf::Color(255, 0, 0, 255), sf::Color(0, 0, 0, 255));
    fig1->getStats()->hp = 100;

    auto fig2 = std::make_shared<Rectangulo>(
        200, 100, 350.f,400.f,sf::Color(169, 169, 0, 255), sf::Color(0, 0, 0, 255));
    fig2->getStats()->hp = 100;

    auto fig3 = std::make_shared<Rectangulo>(
        100, 200,100.f,200.f ,sf::Color(0, 0, 255, 255), sf::Color(0, 0, 0, 255));
    fig3->getStats()->hp = 100;

    auto fig4 = std::make_shared<Circulo>(
            10, 200.f,400.f,sf::Color(255, 255, 255, 255), sf::Color(0, 0, 0, 255));
    fig4->setPosicion(300, 600);
    fig4->getStats()->hp = 100;


    // 🔹 Añadir los objetos
    objetos.agregarPool(fig1);
    objetos.agregarPool(fig2);
    objetos.agregarPool(fig3);
    objetos.agregarPool(fig4);
    // ============================================================
    //    ACTIVAR LA CÁMARA LERP CÚBICA Y SEGUIR AL OBJET0 [1]
    // ============================================================
   CE::GestorCamaras::Get().agregarCamara(
        std::make_shared<CE::CamaraLerpCubica>(
            CE::Vector2D{540.f, 360.f},   // centro inicial
            CE::Vector2D{1280.f, 720.f},
            1000.f// tamaño de ventana / vista
        )
    );
    CE::GestorCamaras::Get().setCamaraActiva(1);

    // 🔹 La cámara sigue al segundo rectangulo
    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(objetos[3]);

    inicializar = false;
}

void EscenaLerp::onFinal() { }

    void EscenaLerp::onUpdate(float dt) {

    // Actualiza la cámara primero
    CE::GestorCamaras::Get().onUpdateCamaras(dt);

    const float maxframes = 120.f;
    static int tiempoFrame = 0;
    static unsigned char reversa = 0;

    const CE::Vector2D inicio  = objetos[0]->getTransformada()->posicion;
    const CE::Vector2D control = objetos[1]->getTransformada()->posicion;
    const CE::Vector2D destino = objetos[2]->getTransformada()->posicion;

    auto npos = CE::lerp2(inicio, control, destino, tiempoFrame / maxframes);
    objetos[3]->setPosicion(npos.x, npos.y);

    if (tiempoFrame > maxframes) reversa = 1;
    if (tiempoFrame < 0) reversa = 0;

    reversa ? tiempoFrame-- : tiempoFrame++;

    for (auto& f : objetos.getPool())
        f->onUpdate(dt);

    objetos.borrarPool();
}

void EscenaLerp::onInputs(const CE::Botones& accion) {
    auto p = objetos[1]->getTransformada();

    if (accion.getTipo() == CE::Botones::TipoAccion::OnPress) {
        if (accion.getNombre() == "arriba")
            p->velocidad.y = -400;
        else if (accion.getNombre() == "derecha")
            p->velocidad.x = 400;
        else if (accion.getNombre() == "abajo")
            p->velocidad.y = 400;
        else if (accion.getNombre() == "izquierda")
            p->velocidad.x = -400;
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

void EscenaLerp::onRender() {
    CE::GestorCamaras::Get().onRenderCamara(CE::Render::Get().GetTextura());

    for (auto& f : objetos.getPool())
        CE::Render::Get().AddToDraw(*f);
}

}
