#pragma  once
#include <SFML/Graphics.hpp>
#include "../Primitivos/Objetos.hpp"
#include "../Componentes/IComponentes.hpp"
#include "../Utils/Vector2D.hpp"
namespace  CE
{
    class Camara {
        public:
            Camara(float x, float y, float w, float h);
            Camara(const  Vector2D& pos, const Vector2D& dim);
            virtual ~Camara(){};
            [[nodiscard]] ITransform& getTransform()
            {
                return *mTransform;
            }
            [[nodiscard]] sf::View& getView() const
            {
                return *mView;
            }
            void lockEnObjeto(const std::shared_ptr<Objeto>& obj);
            void setViewSize(float x, float y);
            virtual void onUpdate(float dt);

        public:
            float camWidth;
            float camHeight;
            static int numCamaras;
            std:: string nombre;
            bool estaActivo;
        protected:
            std::shared_ptr<sf::View> mView;
            std::weak_ptr<Objeto>mLockObj;
        //componenetes
            std::shared_ptr<ITransform> mTransform;
    };

    class CamaraCuadro: public Camara
    {
        public:
            CamaraCuadro(const Vector2D& pos, const Vector2D& dim);
            ~CamaraCuadro()override{};
            void onUpdate(float dt) override;
        private:
            float limitex;
            float limitey;
    };

}