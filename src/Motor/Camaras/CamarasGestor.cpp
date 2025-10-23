#include "CamarasGestor.hpp"

#include "Camaras.hpp"

namespace CE
{
    GestorCamaras &GestorCamaras::Get()
    {
        if (!instancia)
                instancia=new GestorCamaras();
        return *instancia;
    }
    void GestorCamaras::agregarCamara(const std::shared_ptr<Camara> &nueva)
    {
        mListaCamaras.push_back(nueva);
    }
    void GestorCamaras::setCamaraActiva(int id)
    {
        if (id>mListaCamaras.size()-1 || id<0) return;
        if (mCamaraActiva.lock())
                mCamaraActiva.lock()->estaActivo=false;
        mCamaraActiva=mListaCamaras[id];
        mCamaraActiva.lock()->estaActivo=true;
    }

    void GestorCamaras::onUpdateCamaras(float dt)
    {
        if(mCamaraActiva.lock())
                mCamaraActiva.lock()->onUpdate(dt);
    }

    void GestorCamaras::onRenderCamara(sf::RenderTexture &tex)
    {
        tex.setView(mCamaraActiva.lock()->getView());
    }


}