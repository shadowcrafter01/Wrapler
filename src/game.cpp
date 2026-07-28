#include "init.hpp"


void mainTick()
{
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_FRect rect;
    rect.x = mouseX;
    rect.y = mouseY;
    rect.h = TEX.billGates.height;
    rect.w = TEX.billGates.width;
    SDL_RenderTexture(WIN.prime.renderer.pointer, TEX.billGates.pointer, NULL, &rect);

    /* Draw a single triangle with a different color at each vertex. Center this one and make it grow and shrink. */
    /* You always draw triangles with this, but you can string triangles together to form polygons. */
    SDL_Vertex vertices[4];
    const float size = 200.0f;
    SDL_zeroa(vertices);
    vertices[0].position.x = mouseX;
    vertices[0].position.y = mouseY;
    vertices[0].color.r = 1.0f;
    vertices[0].color.a = 1.0f;
    vertices[1].position.x = ((WIN.prime.size.x) + size) / 2.0f;
    vertices[1].position.y = ((WIN.prime.size.y) + size) / 2.0f;
    vertices[1].color.g = 1.0f;
    vertices[1].color.a = 1.0f;
    vertices[2].position.x = ((WIN.prime.size.x) - size) / 2.0f;
    vertices[2].position.y = ((WIN.prime.size.y) + size) / 2.0f;
    vertices[2].color.b = 1.0f;
    vertices[2].color.a = 1.0f;
    SDL_RenderGeometry(WIN.prime.renderer.pointer, NULL, vertices, 3, NULL, 0);

    int w = 0, h = 0;
    int text_w = 0, text_h = 0;
    float x, y;
    Uint64 now = SDL_GetTicks();
    if ((now - last_check) >= 100)
    {
        char string[6];
        SDL_snprintf(string, sizeof(string), "%.2f", ENG_Timer.FPS);
        TTF_SetTextString(text, string, 0);

        last_check = now;
    }
    SDL_GetRenderOutputSize(WIN.prime.renderer.pointer, &w, &h);
    TTF_GetTextSize(text, &text_w, &text_h);
    x = (float)(w - text_w) / 2;
    y = (float)(h - text_h) / 2;
    TTF_DrawRendererText(text, x, y);
}