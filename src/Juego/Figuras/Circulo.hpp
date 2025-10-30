#pragma once
#include <Motor/Primitivos/Objetos.hpp>
#include <SFML/Graphics.hpp>
#include "Figuras.hpp"

namespace IVJ{
class Circulo:public Figuras {
public:
    explicit Circulo(float radio,
        const sf::Color& rcolor, const sf::Color &ccolor);
    ~Circulo() override{};
    float getArea() override;
    void setPosicion(float x,float y);
    void draw(sf::RenderTarget& target,sf::RenderStates state)const override;
    void onUpdate(float dt) override;
    std::string toString() override {
        auto trans = getTransformada();
        auto pos = circ_img.getPosition(); // ← usa la posición real del rectángulo en pantalla

        std::ostringstream ss;
        ss << nombre->nombre
           << " | Pos: (" << pos.x << ", " << pos.y << ")"
            << " | Vel: (" << trans->velocidad.x << ", " << trans->velocidad.y << ")";

        return ss.str();
    }
private:

    sf::CircleShape circ_img;
    float circ_radio;

};
}