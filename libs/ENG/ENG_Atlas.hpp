#ifndef ENG_ATLAS_HPP
#define ENG_ATLAS_HPP

#include "ENG_Texture.hpp"

class ENG_Atlas
{
private:
    /* data */
public:
    ENG_Atlas(ENG_Window *window, const char *path, Vector2<int> image_size) : path{path},
                                                                               renderer{window->renderer.pointer}
    {
        ENG_Console::LogLoadStart((std::string) "Loading atlas [" + path + "]");

        surface = IMG_Load(path);
        if (surface == NULL)
        {
            ENG_Console::LogLoadEnd(false);
            return;
        }
        size = Vector2<int>(surface->w, surface->h);
        pointer = SDL_CreateTextureFromSurface(window->renderer, surface);
        if (pointer == NULL)
        {
            ENG_Console::LogLoadEnd(false);
            return;
        }
        ENG_Console::LogLoadEnd(true);
        state = true;
    }
    ENG_Atlas(ENG_Texture *texture, Vector2<int> image_size) : imageSize{image_size}
    {
        path = texture->path;
        surface = texture->surface;
        size = texture->size;
        pointer = texture->pointer;
        renderer = texture->renderer;

        state = true;
    }

    

    Vector2<double> imageSize;
    SDL_Renderer *renderer;
    const char *path;
    SDL_Texture *pointer;
    SDL_Surface *surface;
    bool state = false;
    Vector2<int> size;
};

#endif