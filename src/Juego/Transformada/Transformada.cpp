#include "Transformada.h"

namespace CE {

    Transformada::Transformada()
        : posicion(0.f, 0.f),
          posicionFinal(0.f, 0.f),
          velocidad(0.f, 0.f),
          velocidadAngular(1.f),
          angulo(0.f),
          radio(30.f) {}

    const sf::Vector2f& Transformada::getPosicion() const { return posicion; }
    void Transformada::setPosicion(const sf::Vector2f& pos) { posicion = pos; }

    const sf::Vector2f& Transformada::getPosicionFinal() const { return posicionFinal; }
    void Transformada::setPosicionFinal(const sf::Vector2f& pos) { posicionFinal = pos; }

    const sf::Vector2f& Transformada::getVelocidad() const { return velocidad; }
    void Transformada::setVelocidad(const sf::Vector2f& vel) { velocidad = vel; }

    float Transformada::getVelocidadAngular() const { return velocidadAngular; }
    void Transformada::setVelocidadAngular(float va) { velocidadAngular = va; }

    float Transformada::getAngulo() const { return angulo; }
    void Transformada::setAngulo(float a) { angulo = a; }

    float Transformada::getRadio() const { return radio; }
    void Transformada::setRadio(float r) { radio = r; }

}
