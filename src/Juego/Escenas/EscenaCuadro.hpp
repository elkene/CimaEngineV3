#pragma once
#include "../../Motor/Primitivos/Escena.hpp"
#include "../objetos/Entidad.hpp"
#include "../objetos/TileMap.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
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
        std::shared_ptr<Entidad> vigilante;
        std::shared_ptr<Entidad> campfire;
        sf::Music musicaFondo;


        //Agregamos el mapas
        TileMap bg[2];
        std::vector<IVJ::TileMap> parallaxLayers;
        // Función para crear fogatas
        std::shared_ptr<Entidad> crearCampfire(float x, float y);
    };

}
