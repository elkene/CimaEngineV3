#include "Camaras.hpp"

#include <cmath>

#include "../GUI/GLogger.hpp"
namespace CE
{
    int Camara::numCamaras=0;
    Camara::Camara(float x, float y, float w, float h)
    :camWidth{w}, camHeight{h}, estaActivo{false}
    {
        mTransform=std::make_shared<ITransform>(Vector2D{x,y}, Vector2D{0,0},0);
        mView=std::make_shared<sf::View>(sf::FloatRect{{x,y},{w,h}});
        mView->setCenter({camWidth/2.f,camHeight/2.f});
        Camara::numCamaras++;
        nombre="Camara Default #"+std::to_string(Camara::numCamaras);
    }
    Camara::Camara(const Vector2D &pos, const Vector2D &dim)
    :camWidth{dim.x},camHeight{dim.y},estaActivo{false}
    {
        mTransform=std::make_shared<ITransform>(pos,Vector2D{0,0},0);
        mView=std::make_shared<sf::View>(
            sf::FloatRect{{0,0},{camWidth,camHeight}});
        mView->setCenter({camWidth/2.f,camHeight/2.f});
        Camara::numCamaras++;
        nombre="Camara Default #"+std::to_string(Camara::numCamaras);
    }
////////////////////////////////////////////////////////////////////////////
CamaraCuadro::CamaraCuadro(const Vector2D &pos, const Vector2D &dim)
    :Camara{pos,dim}, limitex{dim.x}, limitey{dim.y}
    {
        nombre="Camara Default #"+std::to_string(Camara::numCamaras);

    }
    void CamaraCuadro::onUpdate(float dt)
    {
        Camara::onUpdate(dt);
        if (!mLockObj.lock()) return;

        auto mitad=Vector2D(camWidth,camHeight).escala(0.5f);
        auto objTrans=mLockObj.lock()->getTransformada();
        auto opos=objTrans->posicion;
        std::string log="Obj("+std::to_string(opos.x)+
            ","+std::to_string(opos.y)+")";
        std::string log2=nombre+": "+std::to_string(mTransform->posicion.x)+
            ","+std::to_string(mTransform->posicion.y)+")";

        GLogger::Get().agregarLog(log,GLogger::Niveles::LOG_DEBUG);
        GLogger::Get().agregarLog(log2,GLogger::Niveles::LOG_DEBUG);

        if (objTrans->posicion.x>(mTransform->posicion.x+mitad.x))
        {
            mTransform->posicion.x+=camWidth;
            limitex+=limitex;
        }
    }


    void Camara::setViewSize(float x, float y)
    {
        mView->setSize({x,y});
    }
    void Camara::lockEnObjeto(const std::shared_ptr<Objeto> &obj)
    {
        mLockObj=obj;
    }
    void Camara::onUpdate(float dt)
    {
        mView->setCenter({mTransform->posicion.x, mTransform->posicion.y});
    }


}