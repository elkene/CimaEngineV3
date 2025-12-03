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

    // ============ CONFIGURACIÓN DE ZONAS ============
    // Zona donde se desbloquea la cámara (ejemplo: x = 2000)
    camaraDesbloqueadaX = 2800.0f;
    camaraBloqueada = true;  // Inicialmente bloqueada

    // Zona donde se cierra el juego (ejemplo: x = 5000)
    zonaSalidaX = 3300.0f;
    // ===============================================

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
    registrarBotones(sf::Keyboard::Scan::C, "camara");  // ← NUEVA TECLA PARA CÁMARA

    // Crear jugador
    jugador = std::make_shared<Entidad>();
    jugador->getStats()->hp = 100;
    jugador->setPosicion(-3567.5f, 963.0f);
    jugador->getNombre()->nombre = "jugador";

    jugador->addComponente(std::make_shared<CE::ISprite>(
        CE::GestorAssets::Get().getTextura("PP"),
        64, 64,
        1.f
    ));

    jugador->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{45.f, 63.f}));
    jugador->addComponente(std::make_shared<CE::IControl>());
    jugador->addComponente(std::make_shared<IMaquinaEstado>());

    objetos.agregarPool(jugador);

    // Crear vigilante
    vigilante = std::make_shared<Entidad>();
    vigilante->getStats()->hp = 100;
    vigilante->setPosicion(-3817.6f, 963.0f);
    vigilante->getNombre()->nombre = "Vigilante";

    vigilante->addComponente(std::make_shared<CE::ISprite>(
        CE::GestorAssets::Get().getTextura("Vigilante"),
        96, 96,
        1.f
    ));

  //  vigilante->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{96.f, 96.f}));
    vigilante->addComponente(std::make_shared<IMaquinaEstado>());

    auto& fsm_vigilante = vigilante->getComponente<IMaquinaEstado>()->fsm;
    fsm_vigilante = std::make_shared<EnemigoSeguirFSM>(false, jugador, 0.3f);
    fsm_vigilante->onEntrar(*vigilante);

    objetos.agregarPool(vigilante);

    // [código de carga de texturas y objetos ]
    CE::GestorAssets::Get().agregarTextura("fogata", ASSETS "/sprites/Objetos/fogata2.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("cajagrande", ASSETS "/sprites/Objetos/caja_grande.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("estatua1", ASSETS "/sprites/Objetos/estatua1.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("pozo", ASSETS "/sprites/Objetos/pozo.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("antena", ASSETS "/sprites/Objetos/antena.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("cables", ASSETS "/sprites/Objetos/cables.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("muro", ASSETS "/sprites/Objetos/muro.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("barril", ASSETS "/sprites/Objetos/barril.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("mural", ASSETS "/sprites/Objetos/mural.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("carpa", ASSETS "/sprites/Objetos/carpa.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("lapida1", ASSETS "/sprites/Objetos/lapida1.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("lapida2", ASSETS "/sprites/Objetos/lapida2.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("lapida3", ASSETS "/sprites/Objetos/lapida3.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("cuerpo1", ASSETS "/sprites/Objetos/cuerpo1.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("cuerpo2", ASSETS "/sprites/Objetos/cuerpo2.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("cuerpo3", ASSETS "/sprites/Objetos/cuerpo3.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("cuerpo4", ASSETS "/sprites/Objetos/cuerpo4.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("pilademuertos", ASSETS "/sprites/Objetos/pilademuertos.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("roca", ASSETS "/sprites/Objetos/roca.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    CE::GestorAssets::Get().agregarTextura("posteizq", ASSETS "/sprites/Objetos/posteizq.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});

    // [Creación de objetos]
    auto estatua1 = std::make_shared<Entidad>();
    estatua1->getStats()->hp = 100;
    estatua1->setPosicion(-3844, 1001.0f);
    estatua1->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("estatua1"), 2.f));
    estatua1->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{0.f, 486.f}));

    auto pozo = std::make_shared<Entidad>();
    pozo->getStats()->hp = 100;
    pozo->setPosicion(-2860.1f, 906.0f);
    pozo->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("pozo"), 0.8f));

    auto fogata = std::make_shared<Entidad>();
    fogata->getStats()->hp = 100;
    fogata->setPosicion(-3261.3f, 963.0f);
    fogata->addComponente(std::make_shared<CE::ISprite>(
        CE::GestorAssets::Get().getTextura("fogata"), 1.f));

    auto mural = std::make_shared<Entidad>();
    mural->getStats()->hp = 100;
    mural->setPosicion(-2435.3f, 930.0f);
    mural->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("mural"), 1.f));

    carpa = std::make_shared<Entidad>();
    carpa->getStats()->hp = 100;
    carpa->setPosicion(-3386.3f, 951.0f);
    carpa->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("carpa"), 1.f));
    objetos.agregarPool(carpa);

    pilademuertos = std::make_shared<Entidad>();
    pilademuertos->getStats()->hp = 100;
    pilademuertos->setPosicion(-3567.3f, 972.0f);
    pilademuertos->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("pilademuertos"), 1.2f));
    objetos.agregarPool(pilademuertos);

    // [Loops de creación de objetos permanecen igual...]
    for (int i = 0; i < 16; i++) {
        auto antena = std::make_shared<Entidad>();
        antena->getStats()->hp = 100;
        antena->setPosicion(-2355.3f + (i * 310.0f), 850.0f);
        antena->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("antena"), 1.f));
        objetos.agregarPool(antena);
    }

    for (int i = 0; i < 15; i++) {
        auto cable = std::make_shared<Entidad>();
        cable->getStats()->hp = 100;
        cable->setPosicion(-2226.3f + (i * 310.0f), 800.0f);
        cable->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cables"), 1.f));
        objetos.agregarPool(cable);
    }

    for (int i = 0; i < 20; i++) {
        auto muro = std::make_shared<Entidad>();
        muro->getStats()->hp = 100;
        muro->setPosicion(-2226.3f + (i * 250.0f), 931.0f);
        muro->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("muro"), 1.f));
        objetos.agregarPool(muro);
    }

    for (int i = 0; i < 15; i++) {
        if (i % 2 != 0) continue;
        auto barril = std::make_shared<Entidad>();
        barril->getStats()->hp = 100;
        barril->setPosicion(-2166.3f + (i * 250.0f), 961.0f);
        barril->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("barril"), 1.f));
         barril->addComponente(std::make_shared<CE::IBoundingBox>(
               CE::Vector2D{54.f, 70.f}));
        objetos.agregarPool(barril);
    }

    for (int i = 0; i < 5; i++) {
        auto lapida1 = std::make_shared<Entidad>();
        lapida1->getStats()->hp = 100;
        lapida1->setPosicion(-4450.0f + (i * 100.0f), 950.0f);
        lapida1->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("lapida1"), 1.f));
        objetos.agregarPool(lapida1);
    }

    for (int i = 0; i < 5; i++) {
        auto lapida2 = std::make_shared<Entidad>();
        lapida2->getStats()->hp = 100;
        lapida2->setPosicion(-4450.0f + (i * 120.0f), 948.0f);
        lapida2->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("lapida2"), 1.f));
        objetos.agregarPool(lapida2);
    }

    for (int i = 0; i < 5; i++) {
        auto lapida3 = std::make_shared<Entidad>();
        lapida3->getStats()->hp = 100;
        lapida3->setPosicion(-4450.0f + (i * 140.0f), 963.0f);
        lapida3->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("lapida3"), 1.f));
        objetos.agregarPool(lapida3);
    }

    for (int i = 0; i < 15; i++) {
        if (i % 4 != 0) continue;
        auto cuerpo1 = std::make_shared<Entidad>();
        cuerpo1->getStats()->hp = 100;
        cuerpo1->setPosicion(-2095.3f + (i * 250.0f), 981.0f);
        cuerpo1->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cuerpo1"), 1.f));
        objetos.agregarPool(cuerpo1);
    }

    for (int i = 0; i < 15; i++) {
        if (i % 4 != 0) continue;
        auto cuerpo2 = std::make_shared<Entidad>();
        cuerpo2->getStats()->hp = 100;
        cuerpo2->setPosicion(-2166.3f + (i * 250.0f), 912.0f);
        cuerpo2->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cuerpo2"), 1.f));
        objetos.agregarPool(cuerpo2);
    }

    for (int i = 0; i < 15; i++) {
        if (i % 4 != 0) continue;
        auto cuerpo3 = std::make_shared<Entidad>();
        cuerpo3->getStats()->hp = 100;
        cuerpo3->setPosicion(-1661.3f + (i * 250.0f), 970.0f);
        cuerpo3->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cuerpo3"), 1.f));
        objetos.agregarPool(cuerpo3);
    }

    for (int i = 0; i < 15; i++) {
        if (i % 4 != 0) continue;
        auto cuerpo4 = std::make_shared<Entidad>();
        cuerpo4->getStats()->hp = 100;
        cuerpo4->setPosicion(-2166.3f + (i * 250.0f), 981.0f);
        cuerpo4->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cuerpo4"), 1.f));
        objetos.agregarPool(cuerpo4);
    }

    for (int i = 0; i < 15; i++) {
        if (i % 4 != 0) continue;
        auto roca = std::make_shared<Entidad>();
        roca->getStats()->hp = 100;
        roca->setPosicion(-1852.3f + (i * 250.0f), 956.0f);
        roca->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("roca"), 1.f));
        // roca->addComponente(std::make_shared<CE::IBoundingBox>(
        //       CE::Vector2D{192.f, 86.f}));
        rocas.push_back(roca);
        objetos.agregarPool(roca);
    }
    auto posteizq = std::make_shared<Entidad>();
    posteizq->getStats()->hp = 100;
    posteizq->setPosicion(2633.0, 860.0f);
    posteizq->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("posteizq"), 1.2f));

    auto& fsm_init = jugador->getComponente<IMaquinaEstado>()->fsm;
    fsm_init = std::make_shared<IdleFSM>();
    fsm_init->onEntrar(*jugador);



    objetos.agregarPool(fogata);
    objetos.agregarPool(estatua1);
    objetos.agregarPool(pozo);
    objetos.agregarPool(mural);
    objetos.agregarPool(posteizq);

    srand(static_cast<unsigned>(time(nullptr)));

    CE::GestorCamaras::Get().agregarCamara(
        std::make_shared<CE::CamaraCuadro>(
            CE::Vector2D{1920, 1080},
            CE::Vector2D{920.f, 720.f}
        )
    );

    CE::GestorCamaras::Get().setCamaraActiva(1);
    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(jugador);

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
    // ========== VERIFICAR ZONA DE CIERRE DEL JUEGO ==========
    float posJugadorX = jugador->getTransformada()->posicion.x;

    if (posJugadorX >= zonaSalidaX) {
        // Cerrar el juego cuando llegue a esta coordenada
        exit(0);  // O puedes usar: CE::Render::Get().getWindow().close();
    }
    // ========================================================

    // ========== SISTEMA DE DESBLOQUEO DE CÁMARA ==========
    if (camaraBloqueada && posJugadorX >= camaraDesbloqueadaX) {
        // Desbloquear la cámara
        CE::GestorCamaras::Get().getCamaraActiva().unlockObjeto();
        camaraBloqueada = false;
    }

    // Solo bloquear la cámara si aún está bloqueada
    if (camaraBloqueada) {
        CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(jugador);
    }
    // ====================================================

    SistemaMovimientoEntes(objetos.getPool(), dt);

    if (jugador->getTransformada()->velocidad.y > 0) {
        bool aterrizo = ResolverColisionVertical(*jugador, objetos.getPool());
        if (aterrizo) {
            jugador->getTransformada()->velocidad.y = 0.f;
        }
    }

    jugador->inputFSM();

    if (vigilante) {
        vigilante->inputFSM();
    }

    SistemaColisionesEntidades(objetos.getPool());

    for (auto& f : objetos.getPool()) {
        f->onUpdate(dt);
    }

    objetos.borrarPool();
}

void EscenaCuadros::onInputs(const CE::Botones& accion)
{
    auto p = jugador->getTransformada();
    auto c = jugador->getComponente<CE::IControl>();

    if (accion.getTipo() == CE::Botones::TipoAccion::OnPress) {
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
        // ========== TOGGLE DE BLOQUEO DE CÁMARA ==========
        else if (accion.getNombre() == "camara") {
            if (camaraBloqueada) {
                // Si está bloqueada, desbloquear
                CE::GestorCamaras::Get().getCamaraActiva().unlockObjeto();
                camaraBloqueada = false;
            } else {
                // Si está desbloqueada, volver a bloquear
                CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(jugador);
                camaraBloqueada = true;
            }
        }
        // =================================================
    }
    else if (accion.getTipo() == CE::Botones::TipoAccion::OnRelease) {
        if (accion.getNombre() == "derecha") {
            c->der = false;
            if (!c->izq) {
                p->velocidad.x = 0;
            }
        }
        else if (accion.getNombre() == "izquierda") {
            c->izq = false;
            if (!c->der) {
                p->velocidad.x = 0;
            }
        }
        else if (accion.getNombre() == "brincar") {
            c->saltar = false;
        }
        else if (accion.getNombre() == "abajo") {
            c->abj = false;
        }
        else if (accion.getNombre() == "correr") {
            c->correr = false;
        }
    }
}

void EscenaCuadros::onRender()
{
    for (auto& b : bg)
        CE::Render::Get().AddToDraw(b);

    for (auto& f : objetos.getPool()) {
        if (f != jugador && f != vigilante)
            CE::Render::Get().AddToDraw(*f);
    }

    if (vigilante)
        CE::Render::Get().AddToDraw(*vigilante);

    CE::Render::Get().AddToDraw(*jugador);

    if (carpa)
        CE::Render::Get().AddToDraw(*carpa);
    if (pilademuertos)
        CE::Render::Get().AddToDraw(*pilademuertos);

    for (auto& r : rocas) {
        if (r)
            CE::Render::Get().AddToDraw(*r);
    }
}

} // namespace IVJ