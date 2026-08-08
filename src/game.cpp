#include "init.hpp"


void mainTick()
{
    

    SDL_FRect rect;
    rect.x = ENG::input.getMousePos().x;
    rect.y = ENG::input.getMousePos().y;
    rect.h = TEX::billGates.height;
    rect.w = TEX::billGates.width;
    SDL_RenderTexture(WIN::primary.renderer.pointer, TEX::billGates.pointer, NULL, &rect);

    /* Draw a single triangle with a different color at each vertex. Center this one and make it grow and shrink. */
    /* You always draw triangles with this, but you can string triangles together to form polygons. */
    SDL_Vertex vertices[4];
    const float size = 200.0f;
    SDL_zeroa(vertices);
    vertices[0].position.x = ENG::input.getMousePos().x;
    vertices[0].position.y = ENG::input.getMousePos().y;
    vertices[0].color.r = 1.0f;
    vertices[0].color.a = 1.0f;
    vertices[1].position.x = ((WIN::primary.size.x) + size) / 2.0f;
    vertices[1].position.y = ((WIN::primary.size.y) + size) / 2.0f;
    vertices[1].color.g = 1.0f;
    vertices[1].color.a = 1.0f;
    vertices[2].position.x = ((WIN::primary.size.x) - size) / 2.0f;
    vertices[2].position.y = ((WIN::primary.size.y) + size) / 2.0f;
    vertices[2].color.b = 1.0f;
    vertices[2].color.a = 1.0f;
    SDL_RenderGeometry(WIN::primary.renderer.pointer, NULL, vertices, 3, NULL, 0);



    
}