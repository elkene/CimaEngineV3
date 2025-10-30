
#pragma once
#include <Motor/Primitivos/Objetos.hpp>
#include <SFML/Graphics.hpp>
#include "Figuras.hpp"

namespace IVJ {
    class Triangulo:public Figuras {
    public:
        explicit Triangulo(float base,float altura,
            const sf::Color& rcolor,const sf::Color &ccolor);
        ~Triangulo() override{};
       float getArea() override;
        void draw(sf::RenderTarget& target,sf::RenderStates state)const override;
        void onUpdate(float dt) override;
        void setPosicion(float x,float y);
        std::string toString() override {
            auto trans = getTransformada();
            auto pos = tri_img.getPosition(); // ← usa la posición real del rectángulo en pantalla

            std::ostringstream ss;
            ss << nombre->nombre
               << " | Pos: (" << pos.x << ", " << pos.y << ")"
                << " | Vel: (" << trans->velocidad.x << ", " << trans->velocidad.y << ")";

            return ss.str();
        }
    private:
        sf::ConvexShape tri_img;
        float tri_base;
        float tri_altura;
    };
}
