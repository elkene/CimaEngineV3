#pragma once

#include <SFML/Graphics.hpp>
#include "../Componentes/IComponentes.hpp"
#include "Motor/Utils/Vector2D.hpp"

namespace CE
{
    class Objeto: public sf::Drawable, public sf::Transformable
    {
    public:
        // Sobrescribimos toString para incluir el tipo
        virtual std::string toString() const {
            return "Objeto de tipo: " + getTipo()+ "-"+getVelocidad();
        }

        // Nuevo método virtual para el tipo
        virtual std::string getTipo() const {
            return "Objeto";
        }

        virtual std::string getVelocidad() const {
            return "Velocidad";
        }


        explicit Objeto();
        virtual ~Objeto() = default;


        void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
        Objeto& addComponente(const std::shared_ptr<IComponentes>& componentes);

        template<typename T> T* getComponente() const
        {
            static_assert(std::is_base_of<IComponentes, T>::value,"Solo derivados de IComponente");
            for (auto& c: componentes)
            {
                T* comp = dynamic_cast<T*>(c.get());
                if (comp != nullptr)
                    return comp;
            }
            return nullptr;
        }

        template<typename T> bool tieneComponente() const
        {
            static_assert(std::is_base_of<IComponentes, T>::value,"Solo derivado de IComponente");
            for (auto& c: componentes)
            {
                T* comp = dynamic_cast<T*>(c.get());
                if (comp != nullptr)
                    return true;
            }
            return false;
        }

        static int getNumObjetos() { return num_objetos; }

        std::shared_ptr<INombre> getNombre() { return nombre; }
        std::shared_ptr<ITransform> getTransformada() { return transform; }

        void setPosicion(float x, float y);
        virtual void onUpdate(float dt) {}

    private:
        static int num_objetos;

    protected:
        std::vector<std::shared_ptr<IComponentes>> componentes;
        std::shared_ptr<INombre> nombre;
        std::shared_ptr<ITransform> transform;
    };

}
