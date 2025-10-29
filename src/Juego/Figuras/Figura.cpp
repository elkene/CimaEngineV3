#include "Figura.hpp"
#include <math.h>

namespace IVJ
{
    // ========================
    // CLASE BASE: Figuras
    // ========================
    Figuras::Figuras(int l, float ejex, float ejey, const sf::Color& relleno, const sf::Color& contorno)
        : CE::Objeto{}, lados{l}, c_relleno(relleno), c_contorno(contorno)
    {
        transform->posicion.x = ejex;
        transform->posicion.y = ejey;
    }

    // ========================
    // RECTÁNGULO
    // ========================
    Rectangulo::Rectangulo(float base, float altura, float ejex, float ejey,
                           const sf::Color& relleno, const sf::Color& contorno)
        : Figuras{4, ejex, ejey, relleno, contorno},
          imagen{sf::RectangleShape{{base, altura}}},
          b{base},
          a{altura}
    {
        imagen.setFillColor(relleno);
        imagen.setOutlineColor(contorno);
        imagen.setOutlineThickness(10.5F);
        imagen.setOrigin({base / 2, altura / 2});
        setPoscion(ejex, ejey);
    }

    void Rectangulo::setPoscion(float x, float y)
    {
        imagen.setPosition({x, y});
    }

    void Rectangulo::draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        state.transform *= getTransform();
        target.draw(imagen);

        sf::CircleShape ancla{10.f};
        ancla.setFillColor(sf::Color::White);
        ancla.setOrigin({10.f, 10.f});
        ancla.setPosition({imagen.getPosition()});
        target.draw(ancla);
    }

    float Rectangulo::area()
    {
        return b * a; // corregido: área = base * altura
    }

    void Rectangulo::loadFromFile(std::istream& is)
    {
        float base, altura, ejex, ejey;
        int rr, rg, rb;
        int cr, cg, cb;

        is >> base >> altura >> ejex >> ejey
           >> rr >> rg >> rb
           >> cr >> cg >> cb;

        a = altura;
        b = base;
        setPoscion(ejex, ejey);
        transform->posicion.x = ejex;
        transform->posicion.y = ejey;

        getTransformada()->velocidad = {25.f, 100.f};

        c_relleno = sf::Color(rr, rg, rb);
        c_contorno = sf::Color(cr, cg, cb);

        imagen.setSize({b, a});
        imagen.setOrigin({b / 2, a / 2});
        imagen.setFillColor(c_relleno);
        imagen.setOutlineColor(c_contorno);

        addComponente(std::make_shared<CE::ITimer>());
    }

    void Rectangulo::onUpdate(float dt)
    {
        imagen.setPosition({
            transform->posicion.x,
            transform->posicion.y
        });
    }

    // ========================
    // CÍRCULO
    // ========================
    Circulo::Circulo(float radio, float ejex, float ejey,
                     const sf::Color& relleno, const sf::Color& contorno)
        : Figuras{1, ejex, ejey, relleno, contorno},
          imagen{sf::CircleShape(radio)},
          r{radio}
    {
        imagen.setFillColor(relleno);
        imagen.setOutlineColor(contorno);
        imagen.setOutlineThickness(2.5F);
        imagen.setOrigin({radio, radio});
        setPoscion(ejex, ejey);
    }

    void Circulo::setPoscion(float x, float y)
    {
        imagen.setPosition({x, y});
    }

    void Circulo::draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        state.transform *= getTransform();
        target.draw(imagen);

        sf::CircleShape ancla{10.f};
        ancla.setFillColor(sf::Color::White);
        ancla.setOrigin({10.f, 10.f});
        ancla.setPosition({imagen.getPosition()});
        target.draw(ancla);
    }

    float Circulo::area()
    {
        return 3.1415926f * (r * r);
    }

    void Circulo::loadFromFile(std::istream& is)
    {
        float radio, ejex, ejey;
        int rr, rg, rb;
        int cr, cg, cb;

        is >> radio >> ejex >> ejey
           >> rr >> rg >> rb
           >> cr >> cg >> cb;

        r = radio;
        setPoscion(ejex, ejey);
        transform->posicion.x = ejex;
        transform->posicion.y = ejey;

        getTransformada()->velocidad = {25.f, 100.f};

        c_relleno = sf::Color(rr, rg, rb);
        c_contorno = sf::Color(cr, cg, cb);

        imagen.setRadius(r);
        imagen.setOrigin({r, r});
        imagen.setFillColor(c_relleno);
        imagen.setOutlineColor(c_contorno);

        addComponente(std::make_shared<CE::ITimer>());
    }

    void Circulo::onUpdate(float dt)
    {
        imagen.setPosition({
            transform->posicion.x,
            transform->posicion.y
        });
    }

    // ========================
    // TRIÁNGULO
    // ========================
    Triangulo::Triangulo(float lado, float ejex, float ejey,
                         const sf::Color& relleno, const sf::Color& contorno)
        : Figuras{3, ejex, ejey, relleno, contorno},
          imagen{sf::ConvexShape{}},
          a{lado}
    {
        imagen.setPointCount(3);
        imagen.setPoint(0, sf::Vector2f(0, 0));
        imagen.setPoint(1, sf::Vector2f(a, 0));
        imagen.setPoint(2, sf::Vector2f(a / 2.f, a));

        imagen.setOrigin(sf::Vector2f(a / 1.5f, a / 1.5f));
        imagen.setFillColor(relleno);
        imagen.setOutlineColor(contorno);
        imagen.setOutlineThickness(2.5F);
        setPoscion(ejex, ejey);
    }

    void Triangulo::setPoscion(float x, float y)
    {
        imagen.setPosition({x, y});
    }

    void Triangulo::draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        state.transform *= getTransform();
        target.draw(imagen);

        sf::CircleShape ancla{10.f};
        ancla.setFillColor(sf::Color::White);
        ancla.setOrigin({10.f, 10.f});
        ancla.setPosition({imagen.getPosition()});
        target.draw(ancla);
    }

    float Triangulo::area()
    {
        float s = (3 * a) / 2;
        return sqrt(s * (s - a) * (s - a) * (s - a));
    }

    void Triangulo::loadFromFile(std::istream& is)
    {
        float lado, ejex, ejey;
        int rr, rg, rb;
        int cr, cg, cb;

        is >> lado >> ejex >> ejey
           >> rr >> rg >> rb
           >> cr >> cg >> cb;

        a = lado;
        setPoscion(ejex, ejey);
        transform->posicion.x = ejex;
        transform->posicion.y = ejey;

        c_relleno = sf::Color(rr, rg, rb);
        c_contorno = sf::Color(cr, cg, cb);

        getTransformada()->velocidad = {25.f, 100.f};

        imagen.setPointCount(3);
        imagen.setPoint(0, sf::Vector2f(a, 0));
        imagen.setPoint(1, sf::Vector2f(0, a));
        imagen.setPoint(2, sf::Vector2f(a / 2.f, a));
        imagen.setOrigin(sf::Vector2f(a / 1.5f, a / 1.5f));
        imagen.setFillColor(c_relleno);
        imagen.setOutlineThickness(3);
        imagen.setOutlineColor(c_contorno);

        addComponente(std::make_shared<CE::ITimer>());
    }

    void Triangulo::onUpdate(float dt)
    {
        imagen.setPosition({
            transform->posicion.x,
            transform->posicion.y
        });
    }

} // namespace IVJ
