#ifndef ENG_ATLAS_HPP
#define ENG_ATLAS_HPP

#include "ENG_Texture.hpp"

class ENG_Atlas
{
private:
    /* data */
public:
    ENG_Atlas(ENG_Window *window, const char *path, Vector2<int> image_size = NULL)
    {
        texture = &ENG_Texture(window, path);

        ENG_Console::LogLoadStart((std::string) "Making Atlas: [" + path + "]");
        if (image_size == NULL)
        {
            state = false;
            ENG_Console::LogLoadEnd(true);
            return;
        }
        if (texture->size.x % imageSize.x != 0 || texture->size.y % imageSize.y != 0)
        {
            state = false;
            ENG_Console::LogLoadEnd(true, "Warning: Bad size parameter");
            return;
        }
        state = true;
        ENG_Console::LogLoadEnd(true);
    }
    ENG_Atlas(ENG_Texture *texture, Vector2<int> image_size = NULL) : imageSize{image_size},
                                                                      texture{texture}
    {
        ENG_Console::LogLoadStart((std::string) "Making Atlas: [" + texture->path + "]");
        if (image_size == NULL)
        {
            state = false;
            ENG_Console::LogLoadEnd(true);
            return;
        }
        if (texture->size.x % imageSize.x != 0 || texture->size.y % imageSize.y != 0)
        {
            state = false;
            ENG_Console::LogLoadEnd(true, "Warning: Bad size parameter");
            return;
        }
        state = true;
        ENG_Console::LogLoadEnd(true);
    }

    void CropTo(Vector2<int> new_pos, Vector2<int> new_size)
    {
        pos = new_pos;
        size = new_size;
    }

//    void AutoCrop(int frame)
//    {
//        if (!state)
//        {
//            if (imageSize == NULL)
//            {
//                return;
//            }
//            if (texture->size.x % imageSize.x != 0 || texture->size.y % imageSize.y != 0)
//            {
//                return;
//            }
//            else
//            {
//                state = true;
//            }
//        }
//
//        size = imageSize;
//        pos = Vector2<int>(imageSize.x*frame,imageSize.);
//    }

    ENG_Texture *texture;
    Vector2<int> imageSize;
    bool state = false;
    Vector2<int> size;
    Vector2<int> pos;
};

#endif