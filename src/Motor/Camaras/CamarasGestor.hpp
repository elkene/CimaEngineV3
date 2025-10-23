#pragma once
#include "Camaras.hpp"
#include <memory>

namespace CE
{
    class GestorCamaras
    {
        public:
            static GestorCamaras& Get();
            void agregarCamara(const std::shared_ptr<Camara>& nueva);
            void setCamaraActiva(int id);
            void onUpdateCamaras(float dt);
            void onRenderCamara(sf::RenderTexture &tex);
            [[nodiscard]] Camara& getCamaraActiva()
            {
                return *mCamaraActiva.lock();
            }

            [[nodiscard]]Camara& getCamara(int id)
            {
                return *mListaCamaras[id];
            }


        private:
                static inline GestorCamaras* instancia=nullptr;
                std::weak_ptr<Camara> mCamaraActiva;
                std::vector<std::shared_ptr<Camara>> mListaCamaras;
    };
}