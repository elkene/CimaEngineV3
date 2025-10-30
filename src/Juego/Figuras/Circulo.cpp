#include "Circulo.hpp"

namespace IVJ {
    Circulo::Circulo(float radio, const sf::Color &rcolor, const sf::Color &ccolor)
    :Figuras{0,rcolor,ccolor},
    circ_img{sf::CircleShape{radio}},
    circ_radio(radio)
    {

    circ_img.setFillColor(rcolor);
    circ_img.setOutlineColor(ccolor);
    circ_img.setOutlineThickness(2.5f);
    circ_img.setOrigin({radio,radio});
        nombre->nombre="Circulo"+std::to_string(CE::Objeto::getNumObjetos());

    }

    void Circulo::draw(sf::RenderTarget& target,sf::RenderStates states)const {
    states.transform *= getTransform();
    target.draw(circ_img);
    sf::CircleShape ancla{5.f};
    ancla.setFillColor(sf::Color::Black);
    ancla.setPosition(circ_img.getPosition());
    target.draw(ancla);
    }
    float Circulo::getArea() {
        return 3.14159f * circ_radio * circ_radio;
    }
    void Circulo::setPosicion(float x,float y) {

        circ_img.setPosition({x,y}); //cambia la posicion del rectangulo en la ventana
        transform->posicion.x = x;
        transform->posicion.y = y;

    }

    void Circulo::onUpdate(float dt) {
        circ_img.setPosition(
            {
                transform->posicion.x,
                transform->posicion.y
            }
            );

    }
    }
