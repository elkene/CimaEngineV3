#pragma once
#include "../../Motor/Primitivos/Escena.hpp"
#include "../objetos/Entidad.hpp"
#include "../objetos/TileMap.hpp"

namespace IVJ {

    class EscenaCuadros : public CE::Escena {
    public:
        EscenaCuadros() : CE::Escena() { }
        void onInit();
        void onFinal();
        void onUpdate(float dt);
        void onInputs(const CE::Botones& accion);
        void onRender();

    private:
        bool inicializar { true };
        std::shared_ptr<Entidad> jugador;
        std::shared_ptr<Entidad> enemigo;
        //Agregamos el mapas
        TileMap bg[2];
        std::vector<IVJ::TileMap> parallaxLayers; 
    };

}
