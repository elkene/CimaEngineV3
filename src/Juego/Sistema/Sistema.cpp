#include "Sistema.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "Juego/Figuras/Figura.hpp"
#include <cmath>
namespace IVJ
{
   void MoverRectangulo(std::shared_ptr<CE::Objeto> e, float dt, float altoVentana)
    {
        auto trans = e->getTransformada();
        trans->posicion.y += trans->velocidad.y * dt;
        std::cout << trans->posicion.x << std::endl;

        if (trans->posicion.y < 0.f || trans->posicion.y > altoVentana)
            trans->velocidad.y = -trans->velocidad.y;
    }

    void MoverTriangulo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentana)
    {
        auto trans = e->getTransformada();

        trans->posicion.x += trans->velocidad.x * dt;

        float amplitud = 50.f;
        float frecuencia = 2.f;
        trans->posicion.y = (altoVentana / 2.f) + amplitud * std::sin(trans->posicion.x * frecuencia * 0.01f);

        if (trans->posicion.x < 0.f || trans->posicion.x > anchoVentana)
        {
            trans->velocidad.x = -trans->velocidad.x;
        }
    }

    void MoverCirculo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentana)
   {
       auto trans = e->getTransformada();

       // Movimiento horizontal base
       trans->posicion.x += trans->velocidad.x * dt;

       // Movimiento circular más lento
       static float angulo = 0.f;              // ángulo en radianes
       float radio = 50.f;                     // radio del círculo
       float velocidadAngular = 1.f;           // menos rápido que antes
       angulo += velocidadAngular * dt;

       // Coordenadas circulares centradas en Y medio
       trans->posicion.y = (altoVentana / 2.f) + radio * std::sin(angulo);
       trans->posicion.x += (radio * 0.2f) * std::cos(angulo);  // factor horizontal reducido

       // Rebote en los bordes
       if (trans->posicion.x < 0.f || trans->posicion.x > anchoVentana)
       {
           trans->velocidad.x = -trans->velocidad.x;
       }

       // Guardar posición previa
       trans->pos_previa = trans->posicion;
   }

    void MoverJugador(std::shared_ptr<CE::Objeto> e, float dt, float altoVentana)
   {
       auto trans = e->getTransformada();
       //trans->posicion.y += trans->velocidad.y * dt;
       trans->posicion.x += trans->velocidad.x * dt;
   }
    void MoverEnemigo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentana)
   {
       auto trans = e->getTransformada();

       // Actualizar posición
       trans->posicion.x += trans->velocidad.x * dt;
       trans->posicion.y += trans->velocidad.y * dt;

       // Rebote horizontal
       if (trans->posicion.x < 0.f || trans->posicion.x > anchoVentana - 50.f)
           trans->velocidad.x = -trans->velocidad.x;

       // Rebote vertical
       if (trans->posicion.y < 0.f || trans->posicion.y > altoVentana - 50.f)
           trans->velocidad.y = -trans->velocidad.y;

       // Guardar posición anterior
       trans->pos_previa = trans->posicion;
   }


    void SistemaMovimientoEntes(const std::vector<std::shared_ptr<CE::Objeto>>& entes, float dt)
   {
       for (auto& e : entes)
       {
           std::cout << "Entidad: " << e->getNombre()->nombre << std::endl;

           if (e->getNombre()->nombre == "Rectangulo")
               MoverRectangulo(e, dt, 720);
           else if (e->getNombre()->nombre == "Triangulo")
               MoverTriangulo(e, dt, 1920, 1080);
           else if (e->getNombre()->nombre == "Circulo")
               MoverCirculo(e, dt, 1920, 1080);
           else if (e->getNombre()->nombre == "jugador")
               MoverJugador(e, dt, 720);
           else if (e->getNombre()->nombre.find("enemigo_") != std::string::npos)
               MoverEnemigo(e, dt, 1080, 720);



       }
   }




}