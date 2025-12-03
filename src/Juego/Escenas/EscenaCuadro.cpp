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
   // CE::GestorAssets::Get().getSonido("xyz").play();

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
    jugador->setPosicion(-3567.5f, 963.0f);
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
    vigilante->setPosicion(-3817.6f, 963.0f);
    vigilante->getNombre()->nombre = "Vigilante";

    // Sprite del vigilante
    vigilante->addComponente(std::make_shared<CE::ISprite>(
        CE::GestorAssets::Get().getTextura("Vigilante"),
        96, 96,
        1.f
    ));

    // Componentes esenciales para el vigilante
    vigilante->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{96.f, 96.f}));
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
    CE::GestorAssets::Get().agregarTextura("fogata", ASSETS "/sprites/Objetos/fogata2.png",
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
    // antena
    CE::GestorAssets::Get().agregarTextura("antena", ASSETS "/sprites/Objetos/antena.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // cable
    CE::GestorAssets::Get().agregarTextura("cables", ASSETS "/sprites/Objetos/cables.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // muro
   CE::GestorAssets::Get().agregarTextura("muro", ASSETS "/sprites/Objetos/muro.png",
       CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // baril
    CE::GestorAssets::Get().agregarTextura("barril", ASSETS "/sprites/Objetos/barril.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // mural
    CE::GestorAssets::Get().agregarTextura("mural", ASSETS "/sprites/Objetos/mural.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // carpa
    CE::GestorAssets::Get().agregarTextura("carpa", ASSETS "/sprites/Objetos/carpa.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // lapida1
    CE::GestorAssets::Get().agregarTextura("lapida1", ASSETS "/sprites/Objetos/lapida1.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // lapida2
    CE::GestorAssets::Get().agregarTextura("lapida2", ASSETS "/sprites/Objetos/lapida2.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // lapida3
    CE::GestorAssets::Get().agregarTextura("lapida3", ASSETS "/sprites/Objetos/lapida3.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // cuerpo1
    CE::GestorAssets::Get().agregarTextura("cuerpo1", ASSETS "/sprites/Objetos/cuerpo1.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // cuerpo2
    CE::GestorAssets::Get().agregarTextura("cuerpo2", ASSETS "/sprites/Objetos/cuerpo2.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // cuerpo3
    CE::GestorAssets::Get().agregarTextura("cuerpo3", ASSETS "/sprites/Objetos/cuerpo3.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // cuerpo4
    CE::GestorAssets::Get().agregarTextura("cuerpo4", ASSETS "/sprites/Objetos/cuerpo4.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // pilademuertos
    CE::GestorAssets::Get().agregarTextura("pilademuertos", ASSETS "/sprites/Objetos/pilademuertos.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});
    // roca
    CE::GestorAssets::Get().agregarTextura("roca", ASSETS "/sprites/Objetos/roca.png",
        CE::Vector2D{0, 0}, CE::Vector2D{0, 0});




    // // Crear Caja
    // auto caja = std::make_shared<Entidad>();
    // caja->getStats()->hp = 100;
    // caja->setPosicion(-3000.3f, 937.0f);
    // caja->addComponente(std::make_shared<CE::ISprite>(
    //         CE::GestorAssets::Get().getTextura("cajagrande"),
    //         1.f));
    // caja->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{64.f, 0.f}));


//Inicio
    // Estatua
    auto estatua1 = std::make_shared<Entidad>();
    estatua1->getStats()->hp = 100;
    estatua1->setPosicion(-3844, 1001.0f);
    estatua1->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("estatua1"),
            2.f));
    estatua1->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{0.f, 486.f}));

    // Pozo
    auto pozo = std::make_shared<Entidad>();
    pozo->getStats()->hp = 100;
    pozo->setPosicion(-2860.1f, 906.0f);
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

    // Crear Mural
    auto mural = std::make_shared<Entidad>();
    mural->getStats()->hp = 100;
    mural->setPosicion(-2435.3f, 930.0f);
    mural->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("mural"),
            1.f));
    //mural->addComponente(std::make_shared<CE::IBoundingBox>(CE::Vector2D{64.f, 0.f}));
    // Crear carpa
    carpa = std::make_shared<Entidad>();
    carpa->getStats()->hp = 100;
    carpa->setPosicion(-3386.3f, 951.0f);
    carpa->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("carpa"),
            1.f));
    objetos.agregarPool(carpa);

    // Crear pilademuertos
    pilademuertos = std::make_shared<Entidad>();
    pilademuertos->getStats()->hp = 100;
    pilademuertos->setPosicion(-3567.3f, 972.0f);
    pilademuertos->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("pilademuertos"),
            1.2f));
    objetos.agregarPool(pilademuertos);



    //area de muertos
    // ---------------------- CREAR ANTENAS ----------------------
    for (int i = 0; i < 16; i++)
    {
        auto antena = std::make_shared<Entidad>();
        antena->getStats()->hp = 100;

        // Posiciones separadas entre sí
        float x = -2355.3f + (i * 310.0f);
        float y = 850.0f;

        antena->setPosicion(x, y);

        antena->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("antena"),
            1.f
        ));

        objetos.agregarPool(antena);
    }


    // ---------------------- CREAR CABLES ----------------------
    for (int i = 0; i < 15; i++)
    {
        auto cable = std::make_shared<Entidad>();
        cable->getStats()->hp = 100;

        float x = -2226.3f + (i * 310.0f);
        float y = 800.0f;

        cable->setPosicion(x, y);

        cable->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cables"),
            1.f
        ));

        objetos.agregarPool(cable);
    }
    // ---------------------- CREAR muro ----------------------
    for (int i = 0; i < 20; i++)
    {
        auto muro = std::make_shared<Entidad>();
        muro->getStats()->hp = 100;
        float y = 931.0f;
        float x = -2226.3f + (i * 250.0f);


        muro->setPosicion(x, y);

        muro->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("muro"),
            1.f
        ));

        objetos.agregarPool(muro);
    }

    // ---------------------- CREAR Barril (uno sí, uno no) ----------------------
    for (int i = 0; i < 15; i++)
    {
        // Solo crear si el índice es par
        if (i % 2 != 0)
            continue;

        auto barril = std::make_shared<Entidad>();
        barril->getStats()->hp = 100;

        float y = 961.0f;
        float x = -2166.3f + (i * 250.0f);

        barril->setPosicion(x, y);

        barril->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("barril"),
            1.f
        ));

        objetos.agregarPool(barril);
    }
    // ---------------------- CREAR lapida1 ----------------------
    for (int i = 0; i < 5; i++)
    {
        auto lapida1 = std::make_shared<Entidad>();
        lapida1->getStats()->hp = 100;
        float y = 950.0f;
        float x = -4450.0f + (i * 100.0f);


        lapida1->setPosicion(x, y);

        lapida1->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("lapida1"),
            1.f
        ));

        objetos.agregarPool(lapida1);
    }
    // ---------------------- CREAR lapida2 ----------------------
    for (int i = 0; i < 5; i++)
    {
        auto lapida2 = std::make_shared<Entidad>();
        lapida2->getStats()->hp = 100;
        float y = 948.0f;
        float x = -4450.0f + (i * 120.0f);


        lapida2->setPosicion(x, y);

        lapida2->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("lapida2"),
            1.f
        ));

        objetos.agregarPool(lapida2);
    }
    // ---------------------- CREAR lapida3 ----------------------
    for (int i = 0; i < 5; i++)
    {
        auto lapida3 = std::make_shared<Entidad>();
        lapida3->getStats()->hp = 100;
        float y = 963.0f;
        float x = -4450.0f + (i * 140.0f);


        lapida3->setPosicion(x, y);

        lapida3->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("lapida3"),
            1.f
        ));

        objetos.agregarPool(lapida3);
    }

    // ---------------------- CREAR cuerpo1 (uno sí, uno no) ----------------------
    for (int i = 0; i < 15; i++)
    {
        // Solo crear si el índice es par (0,2,4,6...)
        if (i % 4 != 0)
            continue;

        auto cuerpo1 = std::make_shared<Entidad>();
        cuerpo1->getStats()->hp = 100;

        float y = 981.0f;
        float x = -2095.3f + (i * 250.0f);

        cuerpo1->setPosicion(x, y);

        cuerpo1->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cuerpo1"),
            1.f
        ));

        objetos.agregarPool(cuerpo1);
    }

    // ---------------------- CREAR cuerpo2 (uno sí, uno no) ----------------------
    for (int i = 0; i < 15; i++)
    {
        // Solo crear si el índice es par (0,2,4,6...)
        if (i % 4 != 0)
            continue;

        auto cuerpo2 = std::make_shared<Entidad>();
        cuerpo2->getStats()->hp = 100;

        float y = 912.0f;
        float x = -2166.3f + (i * 250.0f);

        cuerpo2->setPosicion(x, y);

        cuerpo2->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cuerpo2"),
            1.f
        ));

        objetos.agregarPool(cuerpo2);
    }
    // ---------------------- CREAR cuerpo3 (uno sí, uno no) ----------------------
    for (int i = 0; i < 15; i++)
    {
        // Solo crear si el índice es par (0,2,4,6...)
        if (i % 4 != 0)
            continue;

        auto cuerpo3 = std::make_shared<Entidad>();
        cuerpo3->getStats()->hp = 100;

        float y = 970.0f;
        float x = -1661.3f + (i * 250.0f);

        cuerpo3->setPosicion(x, y);

        cuerpo3->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cuerpo3"),
            1.f
        ));

        objetos.agregarPool(cuerpo3);
    }
    // ---------------------- CREAR cuerpo4 (uno sí, uno no) ----------------------
    for (int i = 0; i < 15; i++)
    {
        // Solo crear si el índice es par (0,2,4,6...)
        if (i % 4 != 0)
            continue;

        auto cuerpo4 = std::make_shared<Entidad>();
        cuerpo4->getStats()->hp = 100;

        float y = 981.0f;
        float x = -2166.3f + (i * 250.0f);

        cuerpo4->setPosicion(x, y);

        cuerpo4->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("cuerpo4"),
            1.f
        ));

        objetos.agregarPool(cuerpo4);
    }

    // ---------------------- CREAR roca ----------------------
    // Crear múltiples rocas
    for (int i = 0; i < 15; i++)
    {
        if (i % 4 != 0) continue;

        auto roca = std::make_shared<Entidad>();
        roca->getStats()->hp = 100;
        roca->setPosicion(-1852.3f + (i * 250.0f), 956.0f);

        roca->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("roca"),
            1.f
        ));
        roca->addComponente(std::make_shared<CE::IBoundingBox>(
              CE::Vector2D{192.f, 86.f}  // mitad del tamaño del sprite
          ));
        rocas.push_back(roca);  // Guardar en el vector
        objetos.agregarPool(roca);

    }


    // Configurar FSM del jugador
    auto& fsm_init = jugador->getComponente<IMaquinaEstado>()->fsm;
    fsm_init = std::make_shared<IdleFSM>();
    fsm_init->onEntrar(*jugador);

    // Agregar objetos al pool
    objetos.agregarPool(fogata);
    //objetos.agregarPool(caja);
    objetos.agregarPool(estatua1);
    objetos.agregarPool(pozo);
    objetos.agregarPool(mural);

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

    // ========== COLISIONES CON PLATAFORMAS ==========
    // Verificar si el jugador está cayendo y debe aterrizar en algo
    if (jugador->getTransformada()->velocidad.y > 0)  // Si está cayendo
    {
        bool aterrizo = ResolverColisionVertical(*jugador, objetos.getPool());

        // Si aterrizó, detener la velocidad vertical
        if (aterrizo)
        {
            jugador->getTransformada()->velocidad.y = 0.f;
        }
    }

    // Actualizar FSM del jugador
    jugador->inputFSM();

    // Actualizar FSM del vigilante (importante para que el enemigo se mueva)
    if (vigilante) {
        vigilante->inputFSM();
    }

    // Centrar cámara en el jugador
    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(jugador);

    // Sistema de colisiones horizontales (para chocar con objetos)
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
    else if (accion.getTipo() == CE::Botones::TipoAccion::OnRelease)
    {
        // 🔹 CAMBIO IMPORTANTE: Solo apagar las flags de las teclas que se soltaron
        if (accion.getNombre() == "derecha") {
            c->der = false;
            // Solo detener velocidad si no se está presionando izquierda
            if (!c->izq) {
                p->velocidad.x = 0;
            }
        }
        else if (accion.getNombre() == "izquierda") {
            c->izq = false;
            // Solo detener velocidad si no se está presionando derecha
            if (!c->der) {
                p->velocidad.x = 0;
            }
        }
        else if (accion.getNombre() == "brincar") {
            c->saltar = false;  // Se apaga SOLO cuando se suelta Space
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

    // Dibujar jugador (debajo de la carpa)
    CE::Render::Get().AddToDraw(*jugador);

    // Dibujar carpa AL FINAL para que tape al jugador
    if (carpa)
        CE::Render::Get().AddToDraw(*carpa);
    if (pilademuertos)
        CE::Render::Get().AddToDraw(*pilademuertos);
    // Dibujar todas las rocas AL FINAL
    for (auto& r : rocas)
    {
        if (r)
            CE::Render::Get().AddToDraw(*r);

    }
}

} // namespace IVJ

