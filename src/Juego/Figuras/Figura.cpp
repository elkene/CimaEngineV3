#include "Figura.hpp"
#include "math.h"

namespace IVJ
{
    Figuras::Figuras(int l,  float altura, float ejex,const  sf::Color& relleno,const sf::Color& contorno)
   :CE::Objeto{},lados {l}, c_relleno(relleno), c_contorno(contorno){}

    Rectangulo::Rectangulo(float base, float altura, float ejex, float ejey,const sf::Color& relleno, const sf::Color& contorno)
        :Figuras{4,ejex,ejey,relleno, contorno},
        imagen{sf::RectangleShape{{base,altura}}},
        b{base},
        a{altura}
        {
        nombre->nombre="Rectangulo";

            imagen.setFillColor(relleno);
            imagen.setOutlineColor(contorno);
            imagen.setOutlineThickness(2.5F);
            imagen.setOrigin({base/2,altura/2});
        setPosicion(ejex,ejey);
        addComponente(std::make_shared<CE::ITimer>());
        transform->velocidad = sf::Vector2f(25.f,100.f);

        }

         void Rectangulo::draw(sf::RenderTarget& target, sf::RenderStates state) const
        {
            state.transform *= getTransform();
            target.draw(imagen);
        }
        float Rectangulo::area()
        {
            return b*a;
        }
        void Rectangulo::loadFromFile(std::istream& is)
        {
            float base, altura, ejex, ejey;
            int rr, rg, rb;
            int cr, cg, cb;
            is >> base >> altura >> ejex >> ejey
               >> rr >> rg >> rb
               >> cr >> cg >> cb;

            nombre->nombre="Rectangulo";
            a = altura;
            b = base;

            c_relleno = sf::Color(rr, rg, rb);
            c_contorno = sf::Color(cr, cg, cb);

            imagen.setSize({b, a});
            imagen.setOrigin({b/2, a/2});
            imagen.setFillColor(c_relleno);
            imagen.setOutlineColor(c_contorno);
            setPosicion(ejex,ejey);
            addComponente(std::make_shared<CE::ITimer>());
            transform->velocidad = sf::Vector2f(25.f,100.f);
        }

    void Rectangulo::onUpdate(float dt)
    {
        imagen.setPosition({
            transform->posicion.x,
            transform->posicion.y
        });
    }


    Circulo::Circulo(float radio, float ejex, float ejey, const sf::Color& relleno, const sf::Color& contorno)
        :Figuras{1, ejex, ejey, relleno, contorno},
        imagen{sf::CircleShape{{radio}}},
        r{radio}
    {
        imagen.setFillColor(relleno);
        imagen.setOutlineColor(contorno);
        imagen.setOutlineThickness(2.5F);
        imagen.setOrigin({radio,radio});
    }

    void Circulo::draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        state.transform *= getTransform();
        target.draw(imagen);
    }

    float Circulo::area()
    {
        return  3.141615 * (r*r);
    }

    void Circulo::loadFromFile(std::istream& is) {
        float radio, ejex, ejey;
        int rr, rg, rb;
        int cr, cg, cb;
        is >> radio >> ejex >> ejey
           >> rr >> rg >> rb
           >> cr >> cg >> cb;

        nombre->nombre="Circulo";
        r = radio;

        c_relleno = sf::Color(rr, rg, rb);
        c_contorno = sf::Color(cr, cg, cb);

        imagen.setRadius(r);
        imagen.setOrigin(sf::Vector2f(r, r));
        imagen.setFillColor(c_relleno);
        imagen.setOutlineThickness(3);
        imagen.setOutlineColor(c_contorno);
        setPosicion(ejex,ejey);
        addComponente(std::make_shared<CE::ITimer>());
        transform->velocidad = sf::Vector2f(25.f,100.f);

    }

    void Circulo::onUpdate(float dt)
    {
        imagen.setPosition({
            transform->posicion.x,
            transform->posicion.y
        });
    }

    Triangulo::Triangulo(float lado,  float ejex, float ejey, const sf::Color& relleno, const sf::Color& contorno)
      :Figuras{3,ejex,ejey,relleno, contorno},
      imagen{sf::CircleShape{{}}},
      a{lado}
    {
        nombre->nombre="Triangulo";
        this->a=lado;

        transform->posicion.x = ejex;
        transform->posicion.y = ejey;
        transform->velocidad = {25.f,100.f};

        imagen.setRadius(a);
        imagen.setPointCount(3);
        imagen.setOrigin(sf::Vector2f(a, a ));
        imagen.setFillColor(c_relleno);
        imagen.setOutlineThickness(3);
        imagen.setOutlineColor(c_contorno);
        setPosicion(ejex,ejey);
        addComponente(std::make_shared<CE::ITimer>());

    }

    void Triangulo::draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        state.transform *= getTransform();
        target.draw(imagen);
    }

    float Triangulo::area()
    {
        float s=3*a/2;
        return  sqrt (s*(s-a)*(s-a)*(s-a));
    }

    void Triangulo::loadFromFile(std::istream& is) {
        float lado, ejex, ejey;
        int rr, rg, rb; // relleno
        int cr, cg, cb; // contorno
        is >> lado >> ejex >> ejey
           >> rr >> rg >> rb
           >> cr >> cg >> cb;

        nombre->nombre="Triangulo";
        this->a=lado;

        transform->posicion.x = ejex;
        transform->posicion.y = ejey;
        transform->velocidad = {25.f,100.f};
        c_relleno = sf::Color(rr, rg, rb);
        c_contorno = sf::Color(cr, cg, cb);

        imagen.setRadius(a);
        imagen.setPointCount(3);
        imagen.setOrigin(sf::Vector2f(a, a ));
        imagen.setFillColor(c_relleno);
        imagen.setOutlineThickness(3);
        imagen.setOutlineColor(c_contorno);
        setPosicion(ejex,ejey);
        addComponente(std::make_shared<CE::ITimer>());

    }

    void Triangulo::onUpdate(float dt)
    {
        imagen.setPosition({
            transform->posicion.x,
            transform->posicion.y
        });
    }

}