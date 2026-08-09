#ifndef ENG_DRAWTOOLS_HPP
#define ENG_DRAWTOOLS_HPP

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "ENG_Camera.hpp"
#include "ENG_Texture.hpp"
#include "ENG_Font.hpp"

#include "Vector2.hpp"
#include "colorRGBA.hpp"

class ENG_DrawTools
{
private:
    inline static Vector2<double> projectToCamera(ENG_Camera *camera, Vector2<double> vector)
    {
        Vector2<double> out = vector;

        out.x -= camera->position.x;
        out.y -= camera->position.y;

        out *= camera->zoom;

        out.Rotate(-camera->angle);
        out.y *= -1;

        out.x += camera->window->center.x;
        out.y += camera->window->center.y;

        return out;
    }
    inline static bool onscreen(ENG_Camera *camera, Vector2<double> *vector, double size)
    {
        if (vector->x + 2 * size < 0 || vector->y + 2 * size < 0 || vector->x - size > camera->window->size.x || vector->y - size > camera->window->size.y)
        {
            return false;
        }
        return true;
    }

public:
    inline static void DrawTexture(ENG_Camera *camera, ENG_Texture *texture, Vector2<double> position, double size = 1, double angle = 0, colorRGBA color = colorRGBA(255, 255, 255, 255))
    {
        switch (texture->state)
        {
        case -1:
            ENG_Console::LogError((std::string) "Tried to draw invalid texture [" + texture->path + "]");
            return;
            break;
        case 2:
            // do nothing
            break;
        default:
            texture->load(camera->window);
            break;
        }
        Vector2<double> pos = projectToCamera(camera, position);
        SDL_FRect r;
        r.h = size * camera->zoom * texture->size.y;
        r.w = size * camera->zoom * texture->size.x;
        r.x = pos.x - (r.w / 2);
        r.y = pos.y - (r.h / 2);
        Vector2<double> vr(r.x, r.y);

        if (onscreen(camera, &vr, sqrt((r.w / 2 * r.w / 2) + (r.h / 2 * r.h / 2))))
        {
            SDL_SetTextureBlendMode(texture->pointer, SDL_BLENDMODE_BLEND);
            SDL_SetTextureColorMod(texture->pointer, color.red, color.green, color.blue);
            SDL_SetTextureAlphaMod(texture->pointer, color.alpha);
            SDL_RenderTextureRotated(camera->window->renderer, texture->pointer, NULL, &r, angle + camera->angle, NULL, SDL_FLIP_NONE);
        }
    }

    inline static void DrawFont(ENG_Camera *camera, ENG_Font *font, std::string message, Vector2<double> position, double size = 1, double angle = 0, colorRGBA color = colorRGBA(255, 255, 255, 255), Vector2<double> scale = Vector2<double>(1, 1))
    {
        if (message == "" || !font->state)
        {
            return;
        }

        SDL_Surface *textSurface = TTF_RenderText_Solid(font->font, message.c_str(), 0, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(camera->window->renderer, textSurface);
        Vector2<double> pos = projectToCamera(camera, position);
        SDL_FRect r;
        r.h = size * scale.x * camera->zoom * textSurface->h;
        r.w = size * scale.y * camera->zoom * textSurface->w;
        r.x = pos.x;                                          
        r.y = pos.y;                                          
        Vector2<double> vr(r.x, r.y);

        if (onscreen(camera, &vr, sqrt((r.w / 2 * r.w / 2) + (r.h / 2 * r.h / 2))))
        {
            if (!SDL_RenderTextureRotated(camera->window->renderer, texture, NULL, &r, angle + camera->angle, NULL, SDL_FLIP_NONE))
            {
                ENG_Console::LogError("failed to draw text: " + message);
            }
        }
        SDL_DestroySurface(textSurface);
        SDL_DestroyTexture(texture);
    }
};

#endif