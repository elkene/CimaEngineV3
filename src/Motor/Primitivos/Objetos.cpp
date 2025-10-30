#include "Objetos.hpp"
#include <iostream>


namespace CE {
    int Objeto::num_objetos=0;
    Objeto::Objeto() {
        nombre=std::make_shared<INombre>("Objeto " +
            std::to_string(Objeto::num_objetos+1));
        transform=std::make_shared<CE::ITransform>();
        stats=std::make_shared<CE::IStats>();
        Objeto::num_objetos++;
    }
    void Objeto::setPosicion(float x, float y) {
        transform->pos_prev=transform->posicion;
        transform->posicion.x=x;
        transform->posicion.y=y;
    }
    Objeto& Objeto::addComponente(const std::shared_ptr<IComponentes>& componentes) {
        this->componentes.push_back(componentes);
        return *this;
    }
    void Objeto::draw(sf::RenderTarget &target, sf::RenderStates state) const {
        std::cout<<"Objeto::Draw()\n";
    }

}