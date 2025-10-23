#pragma once

#include <Motor/Primitivos/Objetos.hpp>
#include <SFML/Graphics.hpp>
#include "../../Motor/Primitivos/Objetos.hpp"
#include <SFML/Graphics.hpp>

namespace IVJ
{
    class Figuras : public CE::Objeto
    {
    public:
        Figuras(int l, float ejex, float ejey, const sf::Color &relleno, const sf::Color &contorno);
        Figuras(){};
        virtual ~Figuras(){}

        virtual void setPoscion(float x, float y) = 0;
        virtual float area() = 0;
        virtual void loadFromFile(std::istream& is) = 0;

        // Sobreescribimos getTipo para Figuras base
        virtual std::string getTipo() const override {
            return "Figura";
        }

    protected:
        int lados;
        sf::Color c_relleno;
        sf::Color c_contorno;
    };

    class Rectangulo: public Figuras
    {
    public:
        Rectangulo(float base, float altura, float ejex, float ejey, const sf::Color& relleno, const sf::Color& contorno);
        Rectangulo(){};
        ~Rectangulo(){};

        void setPoscion(float x, float y) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        float area() override;
        void loadFromFile(std::istream& is) override;
        void onUpdate(float dt) override;

        // Sobreescritura de getTipo
        std::string getTipo() const override {
            return "Rectangulo";
        }

    private:
        sf::RectangleShape imagen;
        float a;
        float b;
    };

    class Circulo: public Figuras
    {
    public:
        Circulo(float radio, float ejex, float ejey ,const sf::Color& relleno, const sf::Color& contorno);
        Circulo(){};
        ~Circulo(){};

        void setPoscion(float x, float y) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        float area() override;
        void loadFromFile(std::istream& is) override;
        void onUpdate(float dt) override;

        // Sobreescritura de getTipo
        std::string getTipo() const override {
            return "Circulo";
        }

        sf::CircleShape imagen;
        float r;
    };


    class Triangulo: public Figuras
    {
    public:
        Triangulo(float lado, float ejex, float ejey,const sf::Color& relleno, const sf::Color& contorno);
        Triangulo(){};
        ~Triangulo(){};

        void setPoscion(float x, float y) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        float area() override;
        void loadFromFile(std::istream& is) override;
        void onUpdate(float dt) override;

        // Sobreescritura de getTipo
        std::string getTipo() const override {
            return "Triangulo";
        }

    private:
        sf::ConvexShape imagen;
        float a;
    };
}
