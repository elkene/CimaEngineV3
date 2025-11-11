#pragma once

#include <Motor/Primitivos/Objetos.hpp>
#include <SFML/Graphics.hpp>
#include "../../Motor/Primitivos/Objetos.hpp"
#include <SFML/Graphics.hpp>

namespace  IVJ
{
    class Figuras : public CE::Objeto
    {
        public:
            Figuras( int l, float ejex, float ejey,const sf::Color &relleno,const sf::Color &contorno);
            Figuras(){};
            virtual ~Figuras(){}
            virtual float area() = 0;
            virtual void loadFromFile(std::istream& is)=0;
        public:
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
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            float area() override;
            void loadFromFile(std::istream& is) override;
            void onUpdate(float dt) override;

        public:
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
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        float area() override;
        void loadFromFile(std::istream& is) override;
        void onUpdate(float dt) override;

        sf::CircleShape imagen;
        float r;
    };


    class Triangulo: public Figuras
    {
    public:
        Triangulo(float lado, float ejex, float ejey,const sf::Color& relleno, const sf::Color& contorno);
        Triangulo(){};
        ~Triangulo(){};
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        float area() override;
        void loadFromFile(std::istream& is) override;
        void onUpdate(float dt) override;
    public:
        sf::CircleShape imagen;
        float a;
    };
}
/*
#pragma once
#include "../../Motor/Primitivos/Objetos.hpp"
#include <SFML/Graphics.hpp>

namespace IVJ
{
    class Figuras : public CE::Objeto
    {
    public:
        explicit Figuras(int lados,const sf::Color& color,const sf::Color& contorno);
        ~Figuras() override {};
        virtual float getArea() = 0;

        friend std::ostream& operator<<(std::ostream& os,const std::shared_ptr<Figuras>& fig)
        {
            os << "Lados: " << fig->flados
               << "\nRelleno: " << fig->fcrelleno.toInteger()
               << "\nContorno: " << fig->fccontorno.toInteger()
               << "\n";
            return os;
        }

    protected:
        int flados;
        sf::Color fcrelleno;
        sf::Color fccontorno;
    };

    class Rectangulo : public Figuras
    {
    public:
        explicit Rectangulo(float largo, float ancho,
                            const sf::Color& rcolor,
                            const sf::Color& ccolor);
        ~Rectangulo() override {}

        float getArea() override;
        void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
        void onUpdate(float dt) override;

    private:
        float rect_largo;
        float rect_ancho;
        sf::RectangleShape rect_img;
    };

    // las demás figuras abajo...
}*/
