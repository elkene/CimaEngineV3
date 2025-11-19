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

void EscenaCuadros::onInit() {
    if (!inicializar) return;
        //CE::GestorCamaras::Get().setCamaraActiva(1);

        // CE::GestorAssets::Get().agregarTextura("pink",
        //     ASSETS "/sprites/sprites_aliens/alienPink.png",
        //     CE::Vector2D{70,92},CE::Vector2D{66,92});

        // CE::GestorAssets::Get().agregarTextura("barnacle",
        //     ASSETS "/sprites/sprites_aliens/enemies.png",
        //     CE::Vector2D{318,239},CE::Vector2D{51,57});
        //
        // CE::GestorAssets::Get().agregarTextura("bat",
        // ASSETS "/sprites/sprites_aliens/enemies.png",
        //     CE::Vector2D{71,235},CE::Vector2D{70,47});
        //
        // CE::GestorAssets::Get().agregarTextura("slimeGreen",
        // ASSETS "/sprites/sprites_aliens/enemies.png",
        //     CE::Vector2D{140,65},CE::Vector2D{49,34});
        CE::GestorAssets::Get().agregarTextura("Sombras",
              ASSETS "/sprites/SombrasRastreras/Las Sombras Rastreras1.png",
                  CE::Vector2D{0,0},CE::Vector2D{0,0});

        CE::GestorAssets::Get().agregarTextura("Vigilante",
           ASSETS "/sprites/El Vigilante/El Vigilante1.png",
               CE::Vector2D{0,0},CE::Vector2D{0,0});

        CE::GestorAssets::Get().agregarTextura("PP",
          ASSETS "/sprites/ElRenacido/Idle.png",
              CE::Vector2D{0,0},CE::Vector2D{128,32});








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
    //Creamos la entidad para probar el sprite
    jugador=std::make_shared<Entidad>();
    jugador->getStats()->hp=100;
    jugador->setPosicion(-3551.1f,856.8);
    jugador->getNombre()->nombre="jugador";
    jugador->addComponente(std::make_shared<CE::ISprite>(
        CE::GestorAssets::Get().getTextura("PP"),
        32,32,
        2.f));
    jugador->addComponente(std::make_shared<IVJ::IMaquinaEstado>());
    jugador->addComponente(std::make_shared<CE::IControl>());

    auto &fsm_init=jugador->getComponente<IMaquinaEstado>()->fsm;
    fsm_init=std::make_shared<IdleFSM>();
    fsm_init->onEntrar(*jugador);

    objetos.agregarPool(jugador);


    srand(static_cast<unsigned>(time(nullptr))); // Semilla aleatoria
    // 🔹 Crear 100 enemigos con la misma lógica que el jugador
    // Lista de texturas posibles para los enemigos
    std::vector<std::string> texturasEnemigos = {
        "Sombras",
        "Vigilante"
        // puedes agregar más nombres registrados
    };

    // Crear enemigos
    // for (int i = 0; i < 100; ++i) {
    //     auto enemigo = std::make_shared<Entidad>();
    //     enemigo->getStats()->hp = 50;
    //
    //     // Posición inicial: centro de la ventana
    //     enemigo->setPosicion(540.f, 360.f);
    //
    //     // Velocidades aleatorias entre -200 y 200
    //     auto trans = enemigo->getTransformada();
    //     trans->velocidad.x = (rand() % 400 - 200);
    //     trans->velocidad.y = (rand() % 400 - 200);
    //
    //     // Asignar nombre único
    //     enemigo->getNombre()->nombre = "enemigo_" + std::to_string(i);
    //
    //     // 🔹 Elegir textura aleatoria del vector
    //     std::string textura = texturasEnemigos[rand() % texturasEnemigos.size()];
    //
    //     // Añadir sprite con la textura seleccionada
    //     enemigo->addComponente(std::make_shared<CE::ISprite>(
    //         CE::GestorAssets::Get().getTextura(textura),
    //         1.f // escala
    //     ));
    //
    //     objetos.agregarPool(enemigo);
    // }


/*
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
*/
    // 🔹 Cámara
    CE::GestorCamaras::Get().agregarCamara(
        std::make_shared<CE::CamaraCuadro>(
            CE::Vector2D{540, 360}, CE::Vector2D{570.f, 360.f}));
    // CE::GestorCamaras::Get().setCamaraActiva(1);
    //
    // // La cámara sigue al objeto 2
    // CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(objetos[0]);

    //Camara Jugador
    CE::GestorCamaras::Get().setCamaraActiva(1);

    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(jugador);


    //Cargar fondo
    // if(!bg[0].loadTileMap(ASSETS"/mapas/mapa_1_layer_1.txt"))
    //     exit(EXIT_FAILURE);
    // if(!bg[1].loadTileMap(ASSETS"/mapas/mapa_1_layer_2.txt"))
    //     exit(EXIT_FAILURE);
    if(!bg[0].loadTileMap(ASSETS"/mapas/docData2.json"))
        exit(EXIT_FAILURE);
    bg[0].setModoInfinitoHorizontal(true, sf::Vector2f(100000, 100000));

    inicializar = false;
}

void EscenaCuadros::onFinal() { }

void EscenaCuadros::onUpdate(float dt) {
    SistemaMovimientoEntes(objetos.getPool(), dt);
    jugador->inputFSM();
    CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(jugador);
    // 🔹 ACTUALIZAR POSICIÓN DE CÁMARA PARA FONDO INFINITO HORIZONTAL
    auto camara = CE::GestorCamaras::Get().getCamaraActiva();
    auto centroCamara = camara.getView();
    //bg[0].setPosicionCamara(sf::Vector2f(centroCamara.x, centroCamara.y));
    for (auto& f : objetos.getPool())
        f->onUpdate(dt);

    objetos.borrarPool();
}

void EscenaCuadros::onInputs(const CE::Botones& accion) {
    auto p = jugador->getTransformada();
    auto c= jugador->getComponente<CE::IControl>();

    if (accion.getTipo() == CE::Botones::TipoAccion::OnPress) {
        if (accion.getNombre() == "arriba")
        {
            c->arr=true;
            p->velocidad.y = -100;
        }
        else if (accion.getNombre() == "derecha") {
            c->der=true;
            p->velocidad.x = 100;
        }
        else if (accion.getNombre() == "abajo")
        {
            c->abj=true;
            p->velocidad.y = 100;
        }
        else if (accion.getNombre() == "izquierda")
        {
            c->izq=true;
            p->velocidad.x = -100;
        }
        else if (accion.getNombre() == "circulos")
        {
            CE::GestorEscenas::Get().cambiarEscena("Circulos");
        }
    }
    else
        {
            c->arr=false;
            p->velocidad.y = 0;

            c->der=false;
            p->velocidad.x = 0;

            c->abj=false;
            p->velocidad.y = 0;

            c->izq=false;
            p->velocidad.x = 0;


        }
    // else if (accion.getTipo() == CE::Botones::TipoAccion::OnRelease) {
    //     if (accion.getNombre() == "arriba" || accion.getNombre() == "abajo")
    //         p->velocidad.y = 0;
    //     else if (accion.getNombre() == "derecha" || accion.getNombre() == "izquierda")
    //         p->velocidad.x = 0;
    // }
}

void EscenaCuadros::onRender() {
    for (auto& b:bg)
        CE::Render::Get().AddToDraw(b);
    for (auto& f : objetos.getPool())
        CE::Render::Get().AddToDraw(*f);


}

}
