#include "EscenaCuadro.hpp"
#include "../Figuras/Figura.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../Sistema/Sistema.hpp"
#include "Motor/Primitivos/GestorAssets.hpp"
#include "../objetos/TileMap.hpp"
#include "../Maquinas/JugadorFSM/IdleFSM.hpp"

namespace IVJ {

void EscenaCuadros::onInit()
{
    if (!inicializar) return;

    CE::GestorAssets::Get().agregarTextura(
        "Sombras",
        ASSETS "/sprites/SombrasRastreras/Las Sombras Rastreras1.png",
        CE::Vector2D{0,0}, CE::Vector2D{0,0}
    );

    CE::GestorAssets::Get().agregarTextura(
        "Vigilante",
        ASSETS "/sprites/El Vigilante/El Vigilante1.png",
        CE::Vector2D{0,0}, CE::Vector2D{0,0}
    );

    CE::GestorAssets::Get().agregarTextura(
        "PP",
        ASSETS "/sprites/ElRenacido/El Renacido-export.png",
        CE::Vector2D{0,0}, CE::Vector2D{0,0}
    );

    // Registrar controles
    registrarBotones(sf::Keyboard::Scan::W, "arriba");
    registrarBotones(sf::Keyboard::Scan::Up, "arriba");
    registrarBotones(sf::Keyboard::Scan::S, "abajo");
    registrarBotones(sf::Keyboard::Scan::Down, "abajo");
    registrarBotones(sf::Keyboard::Scan::A, "izquierda");
    registrarBotones(sf::Keyboard::Scan::Left, "izquierda");
    registrarBotones(sf::Keyboard::Scan::D, "derecha");
    registrarBotones(sf::Keyboard::Scan::Right, "derecha");
    registrarBotones(sf::Keyboard::Scan::Escape, "circulos");

    // Crear jugador
    jugador = std::make_shared<Entidad>();
    jugador->getStats()->hp = 100;
    jugador->setPosicion(-3261.3f, 970.0f);
    jugador->getNombre()->nombre = "jugador";

    jugador->addComponente(std::make_shared<CE::ISprite>(
        CE::GestorAssets::Get().getTextura("PP"),
        64, 64,
        1.f
    ));

    jugador->addComponente(std::make_shared<IVJ::IMaquinaEstado>());
    jugador->addComponente(std::make_shared<CE::IControl>());
    jugador->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{56.f,78.f}));

    auto& fsm_init = jugador->getComponente<IMaquinaEstado>()->fsm;
    fsm_init = std::make_shared<IdleFSM>();
    fsm_init->onEntrar(*jugador);

    objetos.agregarPool(jugador);

    srand(static_cast<unsigned>(time(nullptr)));

    // Cámara cuadro
    CE::GestorCamaras::Get().agregarCamara(
        std::make_shared<CE::CamaraCuadro>(
            CE::Vector2D{540, 360},
            CE::Vector2D{920.f, 720.f}
        )
    );

    CE::GestorCamaras::Get().setCamaraActiva(1);
    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(jugador);

    // Cargar mapa
    if (!bg[0].loadTileMap(ASSETS "/mapas/docData2.json"))
        exit(EXIT_FAILURE);

    bg[0].setModoInfinitoHorizontal(true, sf::Vector2f(1000000, 1000000));

    inicializar = false;

}

void EscenaCuadros::onFinal()
{
}

void EscenaCuadros::onUpdate(float dt)
{
    SistemaMovimientoEntes(objetos.getPool(), dt);
    jugador->inputFSM();

    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(jugador);

    auto camara = CE::GestorCamaras::Get().getCamaraActiva();
    auto centroCamara = camara.getView();

    for (auto& f : objetos.getPool())
        f->onUpdate(dt);

    objetos.borrarPool();
}

void EscenaCuadros::onInputs(const CE::Botones& accion)
{
    auto p = jugador->getTransformada();
    auto c = jugador->getComponente<CE::IControl>();

    if (accion.getTipo() == CE::Botones::TipoAccion::OnPress)
    {
        if (accion.getNombre() == "arriba") {
            c->arr = true;
            p->velocidad.y = -60;
        }
        else if (accion.getNombre() == "derecha") {
            c->der = true;
            p->velocidad.x = 60;
        }
        else if (accion.getNombre() == "abajo") {
            c->abj = true;
            p->velocidad.y = 60;
        }
        else if (accion.getNombre() == "izquierda") {
            c->izq = true;
            p->velocidad.x = -60;
        }
        else if (accion.getNombre() == "circulos") {
            CE::GestorEscenas::Get().cambiarEscena("Circulos");
        }
    }
    else {
        c->arr = false;
        p->velocidad.y = 0;

        c->der = false;
        p->velocidad.x = 0;

        c->abj = false;
        p->velocidad.y = 0;

        c->izq = false;
        p->velocidad.x = 0;
    }
}

void EscenaCuadros::onRender()
{
    for (auto& b : bg)
        CE::Render::Get().AddToDraw(b);

    for (auto& f : objetos.getPool())
        CE::Render::Get().AddToDraw(*f);
}

} // namespace IVJ
