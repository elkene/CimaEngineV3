#include "Triangulo.hpp"

namespace IVJ {
    Triangulo::Triangulo(float base,float altura,const sf::Color& rcolor,const sf::Color &ccolor)
   : Figuras{3,rcolor,ccolor},
    tri_base{base},tri_altura{altura} {



        tri_img.setPointCount(3); // 3 vértices
        tri_img.setPoint(0, {0.f, altura});        // vértice inferior izquierdo
        tri_img.setPoint(1, {base / 2.f, 0.f});   // vértice superior
        tri_img.setPoint(2, {base, altura});      // vértice inferior derecho

        tri_img.setFillColor(f_relleno);
        tri_img.setOutlineColor(f_contorno);
        tri_img.setOutlineThickness(2.5f);
        tri_img.setOrigin({base / 2.f, altura / 2.f}); // centro para transformaciones
        nombre->nombre="Triangulo"+std::to_string(CE::Objeto::getNumObjetos());
    }
    float Triangulo::getArea() {
        return (tri_base*tri_altura)/2.f;
    }
    void Triangulo::setPosicion(float x,float y) {
        tri_img.setPosition({x,y}); //cambia la posicion del rectangulo en la ventana
        transform->posicion.x = x;
        transform->posicion.y = y;

    }

    void Triangulo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(tri_img, states);

    };
    void Triangulo::onUpdate(float dt) {
        tri_img.setPosition({
            transform->posicion.x,
            transform->posicion.y
        }
        );
    }


}
