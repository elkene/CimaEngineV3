
#pragma once
#include <Motor/Primitivos/Objetos.hpp>
#include <SFML/Graphics.hpp>
#include "Figuras.hpp"

namespace IVJ {
    //Rectangulo hereda de figuras
    class Rectangulo:public Figuras {
    public:
        //Contructor
        explicit Rectangulo(float largo,float ancho,
            const sf::Color& rcolor,const sf::Color &ccolor);
        ~Rectangulo() override{};
        float getArea() override;
        void setPosicion(float x,float y);
        void draw(sf::RenderTarget& target,sf::RenderStates state)const override;
        void onUpdate(float dt) override;
        std::string toString() override {
            auto trans = getTransformada();
            auto pos = rect_img.getPosition(); // ← usa la posición real del rectángulo en pantalla

            std::ostringstream ss;
            ss << nombre->nombre
               << " | Pos: (" << pos.x << ", " << pos.y << ")"
                << " | Vel: (" << trans->velocidad.x << ", " << trans->velocidad.y << ")";

            return ss.str();
        }
        //void setColor(const sf::Color& color) override ;

    private:
        float rect_largo;
        float rect_ancho;
        sf::RectangleShape rect_img;
    };

}
