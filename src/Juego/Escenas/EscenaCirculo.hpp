#pragma once
#include "../../Motor/Primitivos/Escena.hpp"

namespace IVJ {
    class EscenaCirculo: public CE::Escena {
        public:
        EscenaCirculo():CE::Escena{}{};
        void onInit();
        void onFinal();
        void onUpdate(float dt);
        void onInputs(const CE::Botones& accion);
        void onRender();
    private:
        bool inicializar{true};
    };
}