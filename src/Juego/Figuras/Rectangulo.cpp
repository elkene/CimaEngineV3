#include "Rectangulo.hpp"

namespace IVJ {
    //Contructor de Rectangulo (Crea un rectangulo listo para mostrar en pantalla)
    Rectangulo::Rectangulo(float largo,float ancho,const sf::Color& rcolor,const sf::Color& ccolor)
        :Figuras{4,rcolor,ccolor}, //Llama al constructor Figuras con 4 lados y colores recibidos
        rect_largo{largo}, rect_ancho{ancho}, //image es un sf::RectangleShape, la forma de SFML que representa el rectangulo
        rect_img{sf::RectangleShape({largo,ancho})}//w y h guardan ancho y alto
    {
        //Se configura relleno,contorno,grosor y punto de referencia para mover o rotar el rectangulo
        rect_img.setFillColor(f_relleno);
        rect_img.setOutlineColor(f_contorno);
        rect_img.setOutlineThickness(2.f);
        rect_img.setOrigin({rect_largo/2.f,rect_ancho/2.f});
        nombre->nombre="Rectangulo"+std::to_string(CE::Objeto::getNumObjetos());
    }

    float Rectangulo::getArea() {
        return rect_largo*rect_ancho;
    }

    //Metodo draw
    void Rectangulo::draw(sf::RenderTarget& target,sf::RenderStates state)const {
        state.transform *=getTransform();
        target.draw(rect_img);

    };
    void Rectangulo::onUpdate(float dt) {
        rect_img.setPosition(
            {
                transform->posicion.x,
                transform->posicion.y
            }
            );
    }
    void Rectangulo::setPosicion(float x,float y) {
        //Actualiza el objeto grafico
        rect_img.setPosition({x,y}); //cambia la posicion del rectangulo en la ventana
        //Actualizar la logica
        transform->posicion.x = x;
        transform->posicion.y = y;
        //getTransformada()->posicion= {x,y};
    }
    void setColor(const sf::Color& color);


}