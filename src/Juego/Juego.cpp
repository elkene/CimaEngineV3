#include "Juego.hpp"
#include <iostream>
#include <optional>
#include <Motor/Render/Render.hpp>
#include <SFML/Graphics.hpp>
#include "Figuras/Figuras.hpp"
#include "Figuras/Rectangulo.hpp"
#include "Figuras/Triangulo.hpp"
#include "Figuras/Circulo.hpp"
#include <fstream>
#include <sstream>
#include "../Motor/GUI/GLogger.hpp"
#include "Escenas/EscenaCirculo.hpp"
#include "Escenas/EscenaCuadro.hpp"
#include "Motor/Camaras/CamaraGestor.hpp"
#include "Motor/Primitivos/GestorEscenas.hpp"
#include "Motor/Utils/Lista.hpp"
#include "Motor/Utils/Vector2D.hpp"
#include "Sistemas/Sistemas.hpp"
#include "Sistemas/SistemaRectangulo.hpp"
#include "Sistemas/SistemaTriangulo.hpp"
#include "Sistemas/SistemaCirculo.hpp"


namespace IVJ {
    Juego :: Juego() : CE ::GameLayer{} {
        termino = false;
    }

    void Juego::OnInit() {

        /*//Crea un objeto de entrada(ifstream) para abrir y leer
        std::ifstream archivo("../../assets/config/figuras.txt");
        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir figuras.txt\n";
            return;
        }
        //Lee el archivo linea por linea while se acaban los datos
        std::string linea; //linea almacenara una linea completa leida del archivo
        while (std::getline(archivo, linea)) { //bucle para leer el archivo linea por linea
            std::istringstream ss(linea); //convierte la linea en un stream para extraer valores
            //ss ahora contiene linea, la primera linea
            std::string tipo;
            //Rectangulo 144 343 713 884 21 126 90 127 206 149
            //ss>> hara que tipo reciba el primer valor de linea asignandosela
            ss >> tipo; //obtiene el primer valor de la linea(Rectangulo,Triangulo,Circulo)
            //Rectangulo
            //>> avanza al siguiente dato
            if (tipo == "Rectangulo") {
                float ancho, alto, x, y;
                int r1,g1,b1,r2,g2,b2; //Colores de relleno,Colores de Contorno
                //>> avanza al siguiente dato despues del que ya asigno en tipo y ahora asignara el siguiente ancho de linea
                ss >> ancho >> alto >> x >> y >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
                //Figura >> Dimensiones x,y >> Color Relleno>> Color Borde
                //144 343 713 884 21 126 90 127 206 149


                //Crea un rectangulo dinamicamente
               auto rect=std::make_shared<Rectangulo>(
                    ancho, alto,
                    sf::Color(r1,g1,b1),
                    sf::Color(r2,g2,b2)
                );
                rect->addComponente(std::make_shared<CE::ITimer>());
                rect->setPosicion(x, y);
                rectangulos.push_back(rect); //Lo guarda en el vector
                std::cout << "Rectangulo: area= " << rect->getArea() << "\n";
            }

            else if (tipo == "Triangulo") {
                float base, altura, x, y;
                int r1,g1,b1,r2,g2,b2;
                ss >> base >> altura >> x >> y >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
                //Figura >> Dimensiones x,y >> Color Relleno>> Color Borde

                //Crea un rectangulo dinamicamente
                auto tri=std::make_shared<Triangulo>(
                    base, altura,
                    sf::Color(r1,g1,b1),
                    sf::Color(r2,g2,b2)
                );
                tri->addComponente(std::make_shared<CE::ITimer>());
                tri->setPosicion(x, y);
                triangulos.push_back(tri);
                std::cout << "Triangulo: area= " << tri->getArea() << "\n";
            }
            else if (tipo == "Circulo") {
                float radio, x, y;
                int r1,g1,b1,r2,g2,b2;
                ss >> radio >> x >> y >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
                //Figura >> Dimensiones x,y >> Color Relleno>> Color Borde

                //Crea un rectangulo dinamicamente
                auto circ=std::make_shared<Circulo>(
                    radio,
                    sf::Color(r1,g1,b1),
                    sf::Color(r2,g2,b2)
                );
                circ->addComponente(std::make_shared<CE::ITimer>());
                circ->setPosicion(x, y);
                circulos.push_back(circ);
                std::cout << "Circulo: area= " << circ->getArea() << "\n";
            }
        }

        std::string j_txt="Un texto";
        CE::Vector2D P1{100.3,200.1};
        CE::Vector2D P2{500.3,100.1};
        std::cout<<"Magnitud P1" << P1.magnitud()<<std::endl;
        std::cout<<"Magnitud P2" << P2.magnitud() <<std::endl;
        std::cout<<"Dist P1 a P2"<< P1.distancia(P2)<<std::endl;
        std::cout<<"Normalizaicon P1"<< P1.normalizacion() <<std::endl;
        std::cout<<"Normalizacion P2"<< P2.normalizacion()<<std::endl;
        std::cout<<"Norm P1*100: "<< P1.escala(100)<< std::endl;

        CE::Lista<int> listilla;
        listilla.agregarDato(1);
        listilla.agregarDato(2);
        listilla.agregarDato(3);
        listilla.agregarDato(4);
        listilla.agregarDato(5);

        listilla.eliminarDato(2);
        listilla.eliminarDato(2);

        for (auto i=listilla.iterInicio();!listilla.iterTermino();i=listilla.iterSiguiente()) {
            std::cout<<*i<<"\n";
        }
        */
        /*rectangulos[1]->getTransformada()->velocidad.x=15.f;
        CE::GestorCamaras::Get().agregarCamara(
            std::make_shared<CE::CamaraCuadro>(
                CE::Vector2D{0,20},CE::Vector2D{1080,700}
                )
                );
        CE::GestorCamaras::Get().setCamaraActivo(1);
        CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(rectangulos[1]);*/


        //Escenas
        std::cout<<"Inicializando Juego\n";

        CE::GestorEscenas::Get().registrarEscena("Cuadros",std::make_shared<EscenaCuadros>());
        CE::GestorEscenas::Get().registrarEscena("Circulos",std::make_shared<EscenaCirculo>());
        CE::GestorEscenas::Get().cambiarEscena("Cuadros");
        escena_actual=&CE::GestorEscenas::Get().getEscenaActual();






    }
    void Juego::OnInputs(float dt,
        std::optional<sf::Event>& eventos) {
        if (eventos->getIf<sf::Event::Closed>())
            termino=true;

        //INPUTS a l escenas
        CE::Botones::TipoAccion tipo_accion=CE::Botones::TipoAccion::None;
        std::string strAccion="None";
        sf::Keyboard::Scancode scan=sf::Keyboard::Scancode::Comma;
        if (eventos->is<sf::Event::KeyPressed>()) {
            const auto e=eventos->getIf<sf::Event::KeyPressed>();
            tipo_accion=CE::Botones::TipoAccion::OnPress;
            if (e) {
                scan=e->scancode;
                if (escena_actual->getBotones().find(scan)==escena_actual->getBotones().end()) return;
                strAccion=escena_actual->getBotones().at(scan);
            }
        }
        else { //on keyRelease
            const auto e=eventos->getIf<sf::Event::KeyReleased>();
            tipo_accion=CE::Botones::TipoAccion::OnRelease;
            if (e) {
                scan =e->scancode;
                if (escena_actual->getBotones().find(scan)==escena_actual->getBotones().end())
                    strAccion=escena_actual->getBotones().at(scan);
            }
        }
        escena_actual->onInputs(CE::Botones(strAccion,tipo_accion,scan));
    }

    void Juego::OnUpdate(float dt) {

        //funcion recibe coordenadas x,y de una figura
        //y devuelve un nivel de log dependiendo su posicion
        auto nivelSegunPos = [](float x, float y) {
            if (x <=100.f)
                return CE::GLogger::Niveles::LOG_DEBUG; // amarillo
            if (x >= 700.f)
                return CE::GLogger::Niveles::LOG_ERROR; //rojo
            if (std::abs(x - 400.f) <= 50.f && std::abs(y - 300.f) <= 50.f)
                return CE::GLogger::Niveles::LOG_SEVERO; //morado
            return CE::GLogger::Niveles::LOG; // gris: normal
        };


        //GLogger
        //Actualiza la posicion fisica
        SistemaMovimientoRectangulo(rectangulos,dt);
        for (auto &r: rectangulos) {
            //obtiene su posicion actual
            auto pos = r->getTransformada()->posicion;
            //determina el color/nivel del log}
            //pasandole la funcion nivelSegunPos
            auto nivel = nivelSegunPos(pos.x, pos.y);
            //manda el texto a GLogger
            CE::GLogger::Get().agregarLog(r->toString(), nivel);
            //Actualiza su logica
            r->onUpdate(dt);
        }

        SistemaMovimientoTriangulo(triangulos,dt);
        for (auto& t : triangulos) {
            auto pos = t->getTransformada()->posicion;
            auto nivel = nivelSegunPos(pos.x, pos.y);
            CE::GLogger::Get().agregarLog(t->toString(), nivel);
            t->onUpdate(dt);
        }
        SistemaMovimientoCirculo(circulos,dt);
        for (auto& c : circulos) {
            auto pos = c->getTransformada()->posicion;
            auto nivel = nivelSegunPos(pos.x, pos.y);
            CE::GLogger::Get().agregarLog(c->toString(), nivel);
            c->onUpdate(dt);
        }

        //Escenas
        escena_actual=&CE::GestorEscenas::Get().getEscenaActual();
        escena_actual->onUpdate(dt);
    }

    void Juego::OnRender(float dt) {


        //for (auto& c : circulos) CE::Render::Get().AddToDraw(*c);
        //for (auto& r : rectangulos) CE::Render::Get().AddToDraw(*r);
        //for (auto& t : triangulos)  CE::Render::Get().AddToDraw(*t);

        //escenas
        escena_actual->onRender();

    }
}
