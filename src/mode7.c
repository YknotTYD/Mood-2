//mode7.c

#include "../include/main.h"

void render_floor(context_t *context)
{
    int screen_size[2] = {
        context->screen_size[0] / MODE7_SCALE_FACT,
        context->screen_size[1] / MODE7_SCALE_FACT
    };
    int half_height = screen_size[1] / 2;
    SDL_SetRenderDrawColor(context->ren, 0, 0, 255, 255);
    SDL_Surface *surface = SDL_CreateRGBSurface(
        0, UNPACK2(screen_size), 32,
        0xFF000000,
        0x00FF0000,
        0x0000FF00,
        0x000000FF
    );
    SDL_LockSurface(surface);
    uint32_t *pixels = surface->pixels;
    uint32_t *floor_pixels = context->floor->pixels;
    int floor_pitch = context->floor->pitch;
    int color;

    for (int x = 0; x < screen_size[0]; x++) {
        for (int y = half_height; y < screen_size[1]; y++) {

            color = 0x000000FF;
            color |= GRADIENT(y - half_height, half_height, SHIFT_BLUE);
            color |= INVERSE_GRADIENT(y - half_height, half_height, SHIFT_RED);
            color |= GRADIENT(x, screen_size[0], SHIFT_GREEN);

            uint32_t color_ = floor_pixels[(int)(
                (((y - half_height) * 10) % context->floor_height) * floor_pitch / 4.0 +
                (x * 10) % context->floor_width
            )];

            unsigned int r = (((color & 0xFF000000) >> 24) * 1.5 + ((color_ & 0xFF000000) >> 24) * 0.5) / 2;
            unsigned int g = (((color & 0x00FF0000) >> 16) * 1.5 + ((color_ & 0x00FF0000) >> 16) * 0.5) / 2;
            unsigned int b = (((color & 0x0000FF00) >> 8 ) * 1.5 + ((color_ & 0x0000FF00) >> 8)  * 0.5) / 2;

            color = r << 24 | g << 16 | b << 8 | 0XFF;

            pixels[y * surface->pitch / 4 + x] = color;

        }
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(context->ren, surface);
    SDL_UnlockSurface(surface);

    SDL_RenderCopy(context->ren, texture, 0, 0);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return;
}
