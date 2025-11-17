#pragma once
#include "Motor/Componentes/IComponentes.hpp"
#include "Motor/Primitivos/Objetos.hpp"
#include <SFML/Graphics.hpp>
#include "Motor/Utils/Vector2D.hpp"
namespace CE {
    class Camara{
    public:
        Camara(float x, float y, float w, float h);
        Camara(const Vector2D& pos, const Vector2D& dim);
        virtual ~Camara(){};
        [[nodiscard]]ITransform& getTransform()
        {
            return *m_transform;
        }
        [[nodiscard]] sf::View& getView() const {
            return *m_view;
        }
        void lockEnObjeto(const std::shared_ptr<Objeto>& obj);
        void setViewSize(float x, float y);
        virtual void onUpdate(float dt);

    public:
        float cam_width;
        float cam_height;
        static int num_camaras;
        std::string nombre;
        bool esta_activo;
    protected:
        std::shared_ptr<sf::View> m_view;
        std::weak_ptr<Objeto> m_lockObj;
        std::shared_ptr<ITransform> m_transform;
    };

    class CamaraCuadro : public Camara
    {
    public:
        CamaraCuadro(const Vector2D& pos, const Vector2D& dim);
        ~CamaraCuadro() override { }

        void onUpdate(float dt) override;
    private:
        float limitex;
        float limitey;
    };

    class CamaraAreaBox : public Camara
    {
    public:
        CamaraAreaBox(const Vector2D& pos, const Vector2D& dim);
        ~CamaraAreaBox()override { }

        void onUpdate(float dt) override;
    private:
        float dimensionx;
        float dimensiony;
    };

    class CamaraLerpCubica : public Camara
    {
    public:
        CamaraLerpCubica(const Vector2D& pos, const Vector2D& dim, float suavidad);

        virtual void onUpdate(float dt) override;

    private:
        float suavidad;
        float t;
        Vector2D p0, p1, p2, p3;
    };
}

