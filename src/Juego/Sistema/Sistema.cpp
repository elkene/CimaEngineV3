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

    bool SistemaColAABB(CE::Objeto &A, CE::Objeto &B, bool resolucion)
    {
       if (!A.tieneComponente<CE::IBoundingBox>() || !B.tieneComponente<CE::IBoundingBox>())
           return false;
       auto bA=A.getComponente<CE::IBoundingBox>()->tam;
       auto mA= A.getComponente<CE::IBoundingBox>()->mitad;
       auto *pa=&A.getTransformada()->posicion;
       auto prevA=A.getTransformada()->pos_previa;
       auto bB=B.getComponente<CE::IBoundingBox>()->tam;
       auto mB= B.getComponente<CE::IBoundingBox>()->mitad;
       auto pb=&B.getTransformada()->posicion;
       //Calculos
       bool H=pa->y-mA.y < pb->y+bB.y - mB.y && pb->y-mB.y<pa->y+bA.y - mA.y;
       bool V=pa->y-mA.x < pb->x+bB.x - mB.x && pb->x-mB.x<pa->x+bA.x - mA.x;
       bool hay_colision=H&&V;
       if (hay_colision&&resolucion)
           *pa=prevA;
       return hay_colision;
    }

    bool SistemaColAABBMid(CE::Objeto& A, CE::Objeto& B, bool resolucion)
   {
       if (!A.tieneComponente<CE::IBoundingBox>() || !B.tieneComponente<CE::IBoundingBox>())
           return false;

       auto midA = A.getComponente<CE::IBoundingBox>()->mitad;
       auto* pa = &A.getTransformada()->posicion;
       auto prevA = A.getTransformada()->pos_previa;

       auto midB = B.getComponente<CE::IBoundingBox>()->mitad;
       auto* pb = &B.getTransformada()->posicion;

       // cálculos
       float dX = std::abs(pb->x - pa->x);
       float dY = std::abs(pb->y - pa->y);

       float sumMidX = midA.x + midB.x;
       float sumMidY = midA.y + midB.y;

       bool V = sumMidX - dX > 0;
       bool H = sumMidY - dY > 0;

       bool hay_colision = V && H;

       if (resolucion && hay_colision)
           *pa = prevA;

       return hay_colision;
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