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
        ITransform(const Vector2D& pos, const Vector2D& vel, float ang); // solo declaración
        ITransform() = default;
        ~ITransform() override = default;

        Vector2D posicion;
        Vector2D pos_previa;
        Vector2D velocidad;
        float angulo;

        // 🔹 extras para movimientos circulares
        float centroX = 0.f;
        float centroY = 0.f;
        float radio   = 0.f;
        bool inicializado = false;
    };

    class ITimer : public IComponentes
    {
    public:
        ITimer();
        ~ITimer() override = default;

        int frame_actual;
    };
}
