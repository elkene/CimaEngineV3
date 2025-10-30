#include "Figuras.hpp"
#include <utility>
#include "../../../build/Debug/_deps/sfml-src/extlibs/headers/glad/include/glad/gl.h"

namespace IVJ {
    //Constructor Figuras
    Figuras::Figuras(int lados, const sf::Color& color,const sf::Color& contorno)
        :CE::Objeto{},
        f_lados{lados}, f_relleno(std::move(color)),f_contorno(std::move(contorno)) {}
        //lados{l} guarda la cantidad de lados
        //c_relleno{relleno} y c_contorno{contorno} guarda los colores para pintar la figura
        //:CE::Objeto{} significa que Figuras hereda de otra clase llamada CE::Objeto


    }
