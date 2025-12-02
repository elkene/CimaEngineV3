#include "EscenaCuadro.hpp"
#include "../Figuras/Figura.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../Sistema/Sistema.hpp"
#include "Motor/Primitivos/GestorAssets.hpp"
#include "../objetos/TileMap.hpp"
#include "../Maquinas/JugadorFSM/IdleFSM.hpp"
#include "Juego/Maquinas/Enemigos/EnemigoSeguirFSM.hpp"

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

    CE::GestorAssets::Get().agregarSonido("xyz", ASSETS "/sonido/AudioFondo.ogg");
    CE::GestorAssets::Get().getSonido("xyz").setLooping(true);
    CE::GestorAssets::Get().getSonido("xyz").setVolume(25);
    CE::GestorAssets::Get().getSonido("xyz").play();

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
    registrarBotones(sf::Keyboard::Scan::Space, "brincar");
    registrarBotones(sf::Keyboard::Scan::LShift, "correr");

    // Crear jugador
    jugador = std::make_shared<Entidad>();
    jugador->getStats()->hp = 100;
    jugador->setPosicion(-3170.5f, 970.0f);
    jugador->getNombre()->nombre = "jugador";

    jugador->addComponente(std::make_shared<CE::ISprite>(
        CE::GestorAssets::Get().getTextura("PP"),
        64, 64,
        1.f
    ));

    // Agregar componentes esenciales al jugador
    jugador->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{45.f, 63.f}));
    jugador->addComponente(std::make_shared<CE::IControl>()); // Componente de control
    jugador->addComponente(std::make_shared<IMaquinaEstado>()); // Componente de FSM

    objetos.agregarPool(jugador);

    // Crear vigilante (ENEMIGO)
    vigilante = std::make_shared<Entidad>();
    vigilante->getStats()->hp = 100;
    vigilante->setPosicion(-3553.6f, 936.0f);
    vigilante->getNombre()->nombre = "Vigilante";

    // Sprite del vigilante
    vigilante->addComponente(std::make_shared<CE::ISprite>(
        CE::GestorAssets::Get().getTextura("Vigilante"),
        96, 96,
        1.f
    ));

    // Componentes esenciales para el vigilante
    //vigilante->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{150.f, 150.f}));
    vigilante->addComponente(std::make_shared<IMaquinaEstado>()); // ¡IMPORTANTE! Agregar FSM

    // ------------------- AÑADIR ESTO -------------------
    // Configurar FSM del vigilante para que siga al jugador
    auto& fsm_vigilante = vigilante->getComponente<IMaquinaEstado>()->fsm;
    fsm_vigilante = std::make_shared<EnemigoSeguirFSM>(false, jugador, 0.2f);
    fsm_vigilante->onEntrar(*vigilante);
    // ------------------- FIN AÑADIDO -------------------

    objetos.agregarPool(vigilante);

    // Carga de texturas de objetos
    // Fogata
    CE::GestorAssets::Get().agregarTextura("fogata", ASSETS "/sprites/Objetos/fogata.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});

    // CajaGrande
    CE::GestorAssets::Get().agregarTextura("cajagrande", ASSETS "/sprites/Objetos/caja_grande.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});

    // Estatua1
    CE::GestorAssets::Get().agregarTextura("estatua1", ASSETS "/sprites/Objetos/estatua1.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});

    // Pozo
    CE::GestorAssets::Get().agregarTextura("pozo", ASSETS "/sprites/Objetos/pozo.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});

    // Crear Caja
    auto caja = std::make_shared<Entidad>();
    caja->getStats()->hp = 100;
    caja->setPosicion(-3000.3f, 937.0f);
    caja->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cajagrande"),
            1.f));
    caja->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{64.f, 0.f}));

    // Estatua
    auto estatua1 = std::make_shared<Entidad>();
    estatua1->getStats()->hp = 100;
    estatua1->setPosicion(-3355.1f, 955.0f);
    estatua1->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("estatua1"),
            2.f));
    estatua1->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{64.f, 120.f}));

    // Pozo
    auto pozo = std::make_shared<Entidad>();
    pozo->getStats()->hp = 100;
    pozo->setPosicion(-2564.1f, 904.0f);
    pozo->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("pozo"),
            0.8f));

    // Crear fogata
    auto fogata = std::make_shared<Entidad>();
    fogata->getStats()->hp = 100;
    fogata->setPosicion(-3261.3f, 963.0f);
    fogata->addComponente(std::make_shared<CE::ISprite>(
        CE::GestorAssets::Get().getTextura("fogata"),
        1.f));

    // Configurar FSM del jugador
    auto& fsm_init = jugador->getComponente<IMaquinaEstado>()->fsm;
    fsm_init = std::make_shared<IdleFSM>();
    fsm_init->onEntrar(*jugador);

    // Agregar objetos al pool
    objetos.agregarPool(fogata);
    objetos.agregarPool(caja);
    objetos.agregarPool(estatua1);
    objetos.agregarPool(pozo);

    srand(static_cast<unsigned>(time(nullptr)));

    // Cámara cuadro
    CE::GestorCamaras::Get().agregarCamara(
        std::make_shared<CE::CamaraCuadro>(
            CE::Vector2D{1920, 1080},
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
    // Limpieza si es necesaria
}

void EscenaCuadros::onUpdate(float dt)
{
    // Actualizar movimiento de entidades
    SistemaMovimientoEntes(objetos.getPool(), dt);

    // Actualizar FSM del jugador
    jugador->inputFSM();

    // Actualizar FSM del vigilante (importante para que el enemigo se mueva)
    if (vigilante) {
        vigilante->inputFSM(); // Asegúrate de que Entidad tenga este método
    }

    // Centrar cámara en el jugador
    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(jugador);

    // Sistema de colisiones
    SistemaColisionesEntidades(objetos.getPool());

    // Actualizar todas las entidades
    for (auto& f : objetos.getPool())
    {
        f->onUpdate(dt);
    }

    objetos.borrarPool();
}

void EscenaCuadros::onInputs(const CE::Botones& accion)
{
    auto p = jugador->getTransformada();
    auto c = jugador->getComponente<CE::IControl>();

    if (accion.getTipo() == CE::Botones::TipoAccion::OnPress)
    {
        if (accion.getNombre() == "brincar") {
            c->saltar = true;
        }
        else if (accion.getNombre() == "abajo") {
            c->abj = true;
        }
        else if (accion.getNombre() == "correr") {
            c->correr = true;
        }
        else if (accion.getNombre() == "derecha") {
            c->der = true;
            p->velocidad.x = 60;
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
        c->der = false;
        c->izq = false;
        c->saltar = false;
        c->abj = false;
        c->correr = false;

        if (!c->saltar)
            p->velocidad.x = 0;
    }
}

void EscenaCuadros::onRender()
{
    // Dibujar fondo
    for (auto& b : bg)
        CE::Render::Get().AddToDraw(b);

    // Dibujar objetos primero
    for (auto& f : objetos.getPool())
    {
        if (f != jugador && f != vigilante)
            CE::Render::Get().AddToDraw(*f);
    }

    // Dibujar vigilante
    if (vigilante)
        CE::Render::Get().AddToDraw(*vigilante);

    // Dibujar jugador al final (para que esté sobre otros elementos)
    CE::Render::Get().AddToDraw(*jugador);
}

} // namespace IVJ