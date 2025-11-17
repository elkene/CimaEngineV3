#pragma once
#include "../../Motor/Primitivos/Escena.hpp"

namespace IVJ {

    class EscenaLerp : public CE::Escena {
    public:
        EscenaLerp() : CE::Escena() { }

        void onInit();
        void onFinal();
        void onUpdate(float dt);
        void onInputs(const CE::Botones& accion);
        void onRender();

    private:
        bool inicializar { true };
    };

}
