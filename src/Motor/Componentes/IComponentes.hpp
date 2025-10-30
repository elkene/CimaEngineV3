#pragma once
#include <string>
#include "../Utils/Vector2D.hpp"

namespace CE {
    class IComponentes {
        public:
        virtual ~IComponentes() = default;
    };
    class INombre : public IComponentes {
        public:
        INombre(const std::string& nom);
        ~INombre() override{};
    public:
        std::string nombre;
    };
    class ITransform : public IComponentes {
    public:
        ITransform(const Vector2D& pos, const Vector2D& vel,float ang);
        ITransform();
        ~ITransform() override{};
        public:
        Vector2D posicion;
        Vector2D pos_prev;
        Vector2D velocidad;
        float angulo =0.0f;
        float fase=0.0f;
        Vector2D centro;

    };
    class ITimer : public IComponentes {
        public:
        ITimer();
        ~ITimer() override{};
        public:
        int frame_actual;
    };
    class IStats:public IComponentes {
    public :
        ~IStats()override{};
        //8bits=255 maximo
        std::uint8_t hp;
        std::uint8_t hp_max;
        std::uint8_t str;
        std::uint8_t def;
        std::uint8_t agi;
    };

}