//mode7.c

#include "../include/main.h"

void render_floor(context_t *context)
{
    SDL_SetRenderDrawColor(context->ren, 0, 0, 255, 255);
    SDL_Surface *surface = SDL_CreateRGBSurface(
        0, context->screen_size[0] / 4, context->screen_size[1] / 4, 32,
        0xFF000000,
        0x00FF0000,
        0x0000FF00,
        0x000000FF
    );
    SDL_LockSurface(surface);
    uint32_t *pixels = surface->pixels;
    int color;

    for (int x = 0; x < context->screen_size[0] / 4; x++) {
        for (int y = 0; y < context->screen_size[1] / 4; y++) {
            color = 0x000000FF | ((unsigned int)(0xFF * (y / (double)(context->screen_size[1] / 4))) << 8);
            pixels[y * surface->pitch / 4 + x] = color;
        }
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(context->ren, surface);
    SDL_UnlockSurface(surface);
    SDL_UnlockTexture(context->floor.texture);

    SDL_RenderCopy(context->ren, texture, 0, 0);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return;
}
