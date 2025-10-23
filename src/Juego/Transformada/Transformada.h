#pragma once
#include <SFML/System/Vector2.hpp>

namespace CE {

    class Transformada {
    public:
        Transformada();

        // Getters y Setters
        const sf::Vector2f& getPosicion() const;
        void setPosicion(const sf::Vector2f& pos);

        const sf::Vector2f& getPosicionFinal() const;
        void setPosicionFinal(const sf::Vector2f& pos);

        const sf::Vector2f& getVelocidad() const;
        void setVelocidad(const sf::Vector2f& vel);

        float getVelocidadAngular() const;
        void setVelocidadAngular(float va);

        float getAngulo() const;
        void setAngulo(float a);

        float getRadio() const;
        void setRadio(float r);

    public: 
        // Variables accesibles si quieres editarlas directo
        sf::Vector2f posicion;        // centro del movimiento
        sf::Vector2f posicionFinal;   // posición real del objeto
        sf::Vector2f velocidad;       // velocidad lineal (x,y)
        float velocidadAngular;       // rad/s
        float angulo;                 // acumulador de ángulo
        float radio;                  // radio de movimiento circular
    };

}
