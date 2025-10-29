#include "Juego.hpp"
#include <iostream>
#include <Motor/Render/Render.hpp>
#include <SFML/Graphics.hpp>
#include "Figuras/Figura.hpp"
#include "Figuras/FIleLoader.hpp"
#include <memory>
#include <fstream>
#include "Sistema/Sistema.hpp"
#include "../Motor/Utils/Lista.hpp"
#include "../Motor/GUI/GLogger.hpp"
#include "../Motor/Camaras/CamarasGestor.hpp"

namespace IVJ
{
    Juego::Juego()
        : CE::GameLayer{}, texto{font_juego}
    {
        termino = false;
    }

    void Juego::OnInit(void)
    {
        std::cout << "Inicializando Juego\n";

        ARCHIVOS::FIleLoader miloader(ASSETS "/config/figuras.txt");
        objetos = miloader.LoadFile();

        std::string txt = "Un texto";
        CE::Vector2D P1{100.3, 200.1};
        CE::Vector2D P2{500.3, 100.1};

        std::cout << "Magnitud P1: " << P1.magnitud() << std::endl;
        std::cout << "Magnitud P2: " << P2.magnitud() << std::endl;
        std::cout << "Dist P1 a P2: " << P1.distancia(P2) << std::endl;
        std::cout << "Normalizacion P1: " << P1.normalizacion() << std::endl;
        std::cout << "Normalizacion P2: " << P2.normalizacion() << std::endl;
        std::cout << "Norm P1 * 100: " << P1.escala(100) << std::endl;

        CE::Lista<int> listilla;
        listilla.agregarDato(1);
        listilla.agregarDato(2);
        listilla.agregarDato(3);
        listilla.agregarDato(4);
        listilla.agregarDato(5);
        listilla.eliminarDato(2);
        listilla.eliminarDato(2);

        for (auto i = listilla.iterInicio(); !listilla.iterTermino(); i = listilla.iterSiguiente())
        {
            std::cout << *i << "\n";
        }

        while (listilla.getSize() > 0)
            std::cout << listilla.popDato() << "\n";

        if (!font_juego.openFromFile(ASSETS "/fonts/Montserrat-Bold.ttf"))
        {
            std::cout << "Error al cargar font\n";
            exit(1);
        }

        texto.setFont(font_juego);
        texto.setString("HOLA!!!");
        texto.setCharacterSize(50);
        texto.setPosition({500, 300});
        texto.setFillColor(sf::Color::Blue);
        texto.setStyle(sf::Text::Bold | sf::Text::Underlined);

        objetos[0]->getTransformada()->velocidad.x=150.f;
        CE::GestorCamaras::Get().agregarCamara(
            std::make_shared<CE::CamaraCuadro>(
                CE::Vector2D{540,360},CE::Vector2D{1920,1080})
                );
        CE::GestorCamaras::Get().setCamaraActiva(1);
        CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(objetos[0]);
    }

    void Juego::OnInputs(float dt, std::optional<sf::Event> &eventos)
    {
        if (eventos->getIf<sf::Event::Closed>())
            termino = true;
    }

    void Juego::OnUpdate(float dt)
    {
        const float anchoPantalla = 1920.0f;
        const float centroPantalla = anchoPantalla / 2.0f;

        SistemaMovimientoEntes(objetos, dt, anchoPantalla, 1080);

        for (auto &e : objetos)
        {
            // Actualizamos la figura
            e->onUpdate(dt);

            // Obtenemos los datos relevantes
            auto transform = e->getTransformada();
            auto nombre = e->getTipo(); // getTipo() pertenece a CE::Objeto
            float x = transform->posicion.x;
            float y = transform->posicion.y;
            float vx = transform->velocidad.x;
            float vy = transform->velocidad.y;

            // Construimos el mensaje
            std::string info =
                "Nombre: " + nombre +
                " | Posición: (" + std::to_string(x) + ", " + std::to_string(y) + ")" +
                " | Velocidad: (" + std::to_string(vx) + ", " + std::to_string(vy) + ")";

            // Determinamos el nivel de log según la posición en pantalla
            if (x>100.0f) {
                CE::GLogger::Get().agregarLog(info,CE::GLogger::Niveles::LOG);
            }
            if (x < 100.0f)
            {
                CE::GLogger::Get().agregarLog(info, CE::GLogger::Niveles::LOG_DEBUG);
            }
            if (x > anchoPantalla - 100.0f)
            {
                CE::GLogger::Get().agregarLog(info, CE::GLogger::Niveles::LOG_ERROR);
            }
            else if (std::abs(x - centroPantalla) < 50.0f)
            {
                CE::GLogger::Get().agregarLog(info, CE::GLogger::Niveles::LOG_SEVERO);
            }
        }
    }

    void Juego::OnRender(float dt)
    {
        for (auto &figura : objetos)
        {
            CE::Render::Get().AddToDraw(*figura);
        }

        CE::Render::Get().AddToDraw(texto);
    }
}
