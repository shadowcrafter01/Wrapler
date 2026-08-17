#ifndef ENG_DINGUS_HPP
#define ENG_DINGUS_HPP

#include "ENG_Window.hpp"
#include "ENG_Texture.hpp"
#include "ENG_Camera.hpp"
#include "ENG_DrawTools.hpp"
#include "ENG_Timer.hpp"
#include "Vector2.hpp"
#include <vector>

class ENG_Dingus
{
private:
    static std::vector<ENG_Dingus *> &instances()
    {
        static std::vector<ENG_Dingus *> v;
        return v;
    }

public:
    ENG_Dingus()
    {
        instances().push_back(this);
    }
    ENG_Dingus(ENG_Camera *camera) : camera{camera}
    {
        instances().push_back(this);
    }
    ENG_Dingus(ENG_Camera *camera, ENG_Texture *texture) : camera{camera},
                                                           texture{texture}
    {
        instances().push_back(this);
    }
    ~ENG_Dingus()
    {
        std::vector<ENG_Dingus *> &v = instances();
        v.erase(std::remove(v.begin(), v.end(), this), v.end());
    }

    ENG_Camera *camera = nullptr;
    ENG_Texture *texture = nullptr;
    Vector2<double> position = {0, 0};
    Vector2<double> velocity = {0, 0};
    double rotation = 0;
    double size = 1;
    Vector2<double> scale = {1, 1};
    ENG_Timer *timer = nullptr;
    bool active = true;

    void AssignTexture(ENG_Texture *new_texture)
    {
        texture = new_texture;
    }
    void AssignCamera(ENG_Camera *new_camera)
    {
        camera = new_camera;
    }
    void AssignTimer(ENG_Timer *new_timer)
    {
        timer = new_timer;
    }

    void Update()
    {
        if (timer == nullptr)
        {
            position += velocity;
        }
        else
        {
            position += velocity * timer->delta;
        }

        if (texture != NULL && camera != NULL)
        {
            ENG_DrawTools::DrawTexture(camera, texture, position, size, rotation);
        }
    }

    inline static void UpdateAll()
    {
        for (ENG_Dingus *d : instances())
        {
            if (d->active)
            {
                d->Update();
            }
        }
    }
};

#endif