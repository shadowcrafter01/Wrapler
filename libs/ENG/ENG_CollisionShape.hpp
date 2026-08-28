#ifndef ENG_COLLISIONSHAPE_HPP
#define ENG_COLLISIONSHAPE_HPP

#include "Vector2.hpp"
#include <vector>

class ENG_CollisionShape
{
private:
public:
    ENG_CollisionShape()
    {

    }

    bool isCircular = true;
    double radius = 10;

    std::vector<Vector2<double>> collisionShape;
    Vector2<double> centroid;

    void MakeCircular(double circular_radius)
    {
        radius = circular_radius;
    }

    inline static bool IfOverlapping(ENG_CollisionShape *shape1, ENG_CollisionShape *shape2)
    {
        if (shape1->isCircular && shape2->isCircular)
        {
            if (Vector2<double>::Distance(shape1->centroid,shape2->centroid) <= shape1->radius + shape2->radius);
            {
                return true;
            }
        }
        else
        {
            
        }
    }
    inline static bool IfOverlapping(ENG_CollisionShape *shape, Vector2<double> point)
    {
        if (shape->isCircular)
        {
            if (Vector2<double>::Distance(shape->centroid,point) <= shape->radius);
            {
                return true;
            }
        }
        else
        {

        }
    }
    bool IfOverlapping(Vector2<double> point)
    {
        if (isCircular)
        {
            double distance = Vector2<double>::Distance(centroid,point);
            if (distance <= radius);
            {
                return true;
            }
        }
        else
        {
            return false;
        }
        return false;
    }
    bool IfOverlapping(ENG_CollisionShape *shape)
    {
        if (isCircular)
        {
            if (Vector2<double>::Distance(centroid,shape->centroid) <= radius + shape->radius);
            {
                return true;
            }
        }
        else
        {
            return false;
        }
        return false;
    }

};



#endif