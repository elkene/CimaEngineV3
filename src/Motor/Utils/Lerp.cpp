#include "Lerp.hpp"
namespace CE
{
    Vector2D lerp(const Vector2D& init, const Vector2D& dest, float t)
    {
        float tm1=(1-t);
        return Vector2D{
            tm1*init.x+t*init.x,
            tm1*init.y+t*init.y};
    }
    Vector2D lerp2(const Vector2D &init, const Vector2D &ctrl, const Vector2D &dest, float t)
    {
        float tm1=(1-t);
        float tm12=tm1*tm1;
        float t2=t*t;
        return Vector2D{
            tm12*init.x+2*tm1*t*ctrl.x+t2*dest.x,
            tm12*init.y+2*tm1*t*ctrl.y+t2*dest.y};
    }
    Vector2D lerp3(const Vector2D& p0,
               const Vector2D& p1,
               const Vector2D& p2,
               const Vector2D& p3,
               float t)
    {
        float tm1  = (1.0f - t);
        float tm12 = tm1 * tm1;
        float tm13 = tm12 * tm1;

        float t2   = t * t;
        float t3   = t2 * t;

        return Vector2D{
            tm13 * p0.x + 3 * tm12 * t * p1.x + 3 * tm1 * t2 * p2.x + t3 * p3.x,
            tm13 * p0.y + 3 * tm12 * t * p1.y + 3 * tm1 * t2 * p2.y + t3 * p3.y
        };
    }


}