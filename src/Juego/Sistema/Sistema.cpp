#include "Sistema.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "Juego/Figuras/Figura.hpp"
#include <cmath>
namespace IVJ
{
    // ========== FUNCIONES EXISTENTES ==========

    void MoverRectangulo(std::shared_ptr<CE::Objeto> e, float dt, float altoVentana)
    {
        auto trans = e->getTransformada();
        trans->posicion.y += trans->velocidad.y * dt;

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
            trans->velocidad.x = -trans->velocidad.x;
    }

    void MoverCirculo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentana)
    {
        auto trans = e->getTransformada();
        trans->posicion.x += trans->velocidad.x * dt;

        static float angulo = 0.f;
        float radio = 50.f;
        float velocidadAngular = 1.f;
        angulo += velocidadAngular * dt;

        trans->posicion.y = (altoVentana / 2.f) + radio * std::sin(angulo);
        trans->posicion.x += (radio * 0.2f) * std::cos(angulo);

        if (trans->posicion.x < 0.f || trans->posicion.x > anchoVentana)
            trans->velocidad.x = -trans->velocidad.x;

        trans->pos_previa = trans->posicion;
    }

    void MoverJugador(std::shared_ptr<CE::Objeto> e, float dt, float altoVentana)
    {
        auto trans = e->getTransformada();
        trans->posicion.y += trans->velocidad.y * dt;
        trans->posicion.x += trans->velocidad.x * dt;
    }

    void MoverEnemigo(std::shared_ptr<CE::Objeto> e, float dt, float anchoVentana, float altoVentana)
    {
        auto trans = e->getTransformada();
        trans->posicion.x += trans->velocidad.x * dt;
        trans->posicion.y += trans->velocidad.y * dt;

        if (trans->posicion.x < 0.f || trans->posicion.x > anchoVentana - 50.f)
            trans->velocidad.x = -trans->velocidad.x;

        if (trans->posicion.y < 0.f || trans->posicion.y > altoVentana - 50.f)
            trans->velocidad.y = -trans->velocidad.y;

        trans->pos_previa = trans->posicion;
    }

    // ========== NUEVAS FUNCIONES DE COLISIÓN ==========

    bool VerificarSobreObjeto(CE::Objeto& jugador, CE::Objeto& objeto, float tolerancia)
    {
        if (!jugador.tieneComponente<CE::IBoundingBox>() || !objeto.tieneComponente<CE::IBoundingBox>())
            return false;

        auto bbox_jugador = jugador.getComponente<CE::IBoundingBox>();
        auto bbox_objeto = objeto.getComponente<CE::IBoundingBox>();

        auto pos_jugador = jugador.getTransformada()->posicion;
        auto pos_objeto = objeto.getTransformada()->posicion;

        // Límites del jugador
        float jugador_abajo = pos_jugador.y + bbox_jugador->mitad.y;
        float jugador_izq = pos_jugador.x - bbox_jugador->mitad.x;
        float jugador_der = pos_jugador.x + bbox_jugador->mitad.x;

        // Límites del objeto
        float objeto_arriba = pos_objeto.y - bbox_objeto->mitad.y;
        float objeto_izq = pos_objeto.x - bbox_objeto->mitad.x;
        float objeto_der = pos_objeto.x + bbox_objeto->mitad.x;

        // Verificar si está horizontalmente alineado
        bool horizontal_overlap = jugador_der > objeto_izq && jugador_izq < objeto_der;

        // Verificar si está cerca de la parte superior del objeto
        bool sobre_objeto = std::abs(jugador_abajo - objeto_arriba) <= tolerancia;

        return horizontal_overlap && sobre_objeto;
    }

    bool ResolverColisionVertical(CE::Objeto& jugador, const std::vector<std::shared_ptr<CE::Objeto>>& objetos)
    {
        if (!jugador.tieneComponente<CE::IBoundingBox>())
            return false;

        auto bbox_jugador = jugador.getComponente<CE::IBoundingBox>();
        auto pos_jugador = jugador.getTransformada()->posicion;
        auto vel_jugador = jugador.getTransformada()->velocidad;

        float jugador_abajo = pos_jugador.y + bbox_jugador->mitad.y;
        float jugador_izq = pos_jugador.x - bbox_jugador->mitad.x;
        float jugador_der = pos_jugador.x + bbox_jugador->mitad.x;

        // Verificar colisión con el suelo base
        const float SUELO_BASE = 963.f;
        if (jugador_abajo >= SUELO_BASE && vel_jugador.y > 0)
        {
            jugador.setPosicion(pos_jugador.x, SUELO_BASE - bbox_jugador->mitad.y);
            return true;
        }

        // Verificar colisión con objetos sólidos
        for (const auto& objeto : objetos)
        {
            if (objeto.get() == &jugador || !objeto->tieneComponente<CE::IBoundingBox>())
                continue;

            // Lista de objetos sólidos (ajusta según necesites)
            auto nombre_obj = objeto->getNombre()->nombre;
            bool es_solido = (nombre_obj.find("estatua") != std::string::npos ||
                            nombre_obj.find("caja") != std::string::npos ||
                            nombre_obj.find("muro") != std::string::npos ||
                            nombre_obj.find("barril") != std::string::npos ||
                            nombre_obj.find("roca") != std::string::npos ||
                            nombre_obj.find("pozo") != std::string::npos);

            if (!es_solido)
                continue;

            auto bbox_objeto = objeto->getComponente<CE::IBoundingBox>();
            auto pos_objeto = objeto->getTransformada()->posicion;

            float objeto_arriba = pos_objeto.y - bbox_objeto->mitad.y;
            float objeto_abajo = pos_objeto.y + bbox_objeto->mitad.y;
            float objeto_izq = pos_objeto.x - bbox_objeto->mitad.x;
            float objeto_der = pos_objeto.x + bbox_objeto->mitad.x;

            bool horizontal_overlap = jugador_der > objeto_izq && jugador_izq < objeto_der;

            // Verificar si está cayendo sobre el objeto
            if (horizontal_overlap && vel_jugador.y > 0)
            {
                if (jugador_abajo >= objeto_arriba && jugador_abajo <= objeto_arriba + 15.f)
                {
                    // Colocar al jugador exactamente sobre el objeto
                    jugador.setPosicion(pos_jugador.x, objeto_arriba - bbox_jugador->mitad.y);
                    return true;
                }
            }
        }

        return false;
    }

    bool SistemaColAABB(CE::Objeto& A, CE::Objeto& B, bool resolucion)
    {
        if (!A.tieneComponente<CE::IBoundingBox>() || !B.tieneComponente<CE::IBoundingBox>())
            return false;

        auto bA = A.getComponente<CE::IBoundingBox>()->tam;
        auto mA = A.getComponente<CE::IBoundingBox>()->mitad;
        auto* pa = &A.getTransformada()->posicion;
        auto prevA = A.getTransformada()->pos_previa;

        auto bB = B.getComponente<CE::IBoundingBox>()->tam;
        auto mB = B.getComponente<CE::IBoundingBox>()->mitad;
        auto* pb = &B.getTransformada()->posicion;

        float overlapX = (mA.x + mB.x) - std::abs(pb->x - pa->x);
        float overlapY = (mA.y + mB.y) - std::abs(pb->y - pa->y);

        bool haycolision = overlapX > 0 && overlapY > 0;

        if (haycolision && resolucion)
        {
            if (overlapX < overlapY)
            {
                if (pa->x < pb->x)
                    pa->x = pb->x - (mA.x + mB.x);
                else
                    pa->x = pb->x + (mA.x + mB.x);
            }
            else
            {
                if (pa->y < pb->y)
                    pa->y = pb->y - (mA.y + mB.y);
                else
                    pa->y = pb->y + (mA.y + mB.y);
            }
        }

        return haycolision;
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

        float dX = std::abs(pb->x - pa->x);
        float dY = std::abs(pb->y - pa->y);

        float sumMidX = midA.x + midB.x;
        float sumMidY = midA.y + midB.y;

        bool V = sumMidX - dX > 0;
        bool H = sumMidY - dY > 0;

        bool haycolision = V && H;

        if (resolucion && haycolision)
            *pa = prevA;

        return haycolision;
    }

    void SistemaMovimientoEntes(const std::vector<std::shared_ptr<CE::Objeto>>& entes, float dt)
    {
        for (auto& e : entes)
        {
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

    void SistemaColisionesEntidades(const std::vector<std::shared_ptr<CE::Objeto>>& entes)
    {
        std::vector<std::pair<CE::Objeto*, CE::Objeto*>> colisiones;

        for (size_t i = 0; i < entes.size(); ++i)
        {
            for (size_t j = i + 1; j < entes.size(); ++j)
            {
                if (SistemaColAABB(*entes[i], *entes[j], false))
                {
                    colisiones.push_back({entes[i].get(), entes[j].get()});
                }
            }
        }

        for (auto& colision : colisiones)
        {
            SistemaColAABB(*colision.first, *colision.second, true);
        }
    }
}