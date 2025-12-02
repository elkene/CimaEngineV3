#pragma once
#include <string>
#include "../Utils/Vector2D.hpp"

namespace CE
{
    class IComponentes
    {
        public:
            virtual ~IComponentes() = default;
    };

    class INombre : public IComponentes
    {
        public:
            INombre(const std::string& nom);
            ~INombre() override = default;
            std::string nombre;
    };

    class ITransform : public IComponentes
    {
        public:
            ITransform(const Vector2D& pos, const Vector2D& vel, float ang);
            ITransform() = default;
            ~ITransform() override = default ;
        public:
            Vector2D posicion;
            Vector2D pos_previa;
            Vector2D velocidad;
            float angulo;
    };

    class ITimer : public IComponentes
    {
        public:
            ITimer();
            ~ITimer() override = default;
            int frame_actual;
    };

    class IStats: public IComponentes
    {
        public:
        ~IStats()override{};
        std::uint8_t hp;
        std::uint8_t hp_max;
        std::uint8_t str;
        std::uint8_t def;
        std::uint8_t agi;
    };

    class ISprite: public IComponentes
  {
    public:
      explicit ISprite(const sf::Texture& textura, float escala);
        ISprite(const sf::Texture& textura, int w, int h,float escala);
        ~ISprite()override{};
    public:
      sf::Sprite m_sprite;
        int width;
        int height;
        float escala;
    private:
        sf::Texture m_textura;
  };


    class IControl : public IComponentes
    {
        public:
            explicit IControl();
            ~IControl() override {};
        public:
            bool arr;
            bool abj;
            bool izq;
            bool der;
            bool acc;
            bool sacc;
            bool saltar;
            bool correr;
    };

    class IBoundingBox : public IComponentes
    {
        public:
            explicit IBoundingBox (const Vector2D& dim);
            Vector2D tam;
            Vector2D mitad;
    };

}
