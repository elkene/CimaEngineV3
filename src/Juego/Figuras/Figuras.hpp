#pragma once
#include <Motor/Primitivos/Objetos.hpp>
#include <SFML/Graphics.hpp>

namespace IVJ {
    //Figuras hereda de otra clase CE::Objeto
    class Figuras : public CE::Objeto {
    public:
        //virtual void setColor(const sf::Color& color) = 0;
        explicit Figuras(int lados,const sf::Color &color,const sf::Color& contorno);
        ~Figuras() override{};
        virtual float getArea()=0;
        friend std::ostream& operator<<(std::ostream& os,const std::shared_ptr<Figuras>& fig) {
            os<<"lados: "<<fig->f_lados<<
                "\nRelleno: "<<fig->f_relleno.toInteger()<<
                    "\nControno: "<<fig->f_contorno.toInteger()<<
                        "\n";
            return os;
        };
    protected:
        int f_lados;
        sf::Color f_relleno;
        sf::Color f_contorno;
    };

}
