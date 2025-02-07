//mode7.c

#include "../include/main.h"

static color_t get_floor_color(
    context_t *context, color_t *floor_pixels, int floor_pitch,
    int x, int y, int half_height
) {
    color_t color;

    if (ABS(half_height - y) <= 100) {
        return 0x0000FFFF;
    }

    long double ray_angle = context->player->angle -
        (DEG_TO_RAD(context->player->FOV) / 2.0) + (x / (double)context->screen_size[0]) * DEG_TO_RAD(context->player->FOV); //context->player->angles[x];
    double z = (y - half_height) / (double)half_height;
    long double distance = 100 / (z * 0.05);

    long double floor_x = context->player->pos[0] + distance * cosl(ray_angle);
    long double floor_y = context->player->pos[1] + distance * sinl(ray_angle);

    int tx = ABS((int)floor_x) % context->floor_width;
    int ty = ABS((int)floor_y) % context->floor_height;

    color = floor_pixels[(int)(ty * (floor_pitch / 4) + tx)];

    return color;
}

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
    color_t *pixels = surface->pixels;
    color_t *floor_pixels = context->floor->pixels;
    int floor_pitch = context->floor->pitch;
    int color;

    for (int x = 0; x < screen_size[0]; x++) {
        for (int y = half_height; y < screen_size[1]; y++) {

            color = 0x000000FF;
            color |= GRADIENT(y - half_height, half_height, SHIFT_BLUE);
            color |= INVERSE_GRADIENT(y - half_height, half_height, SHIFT_RED);
            color |= GRADIENT(x, screen_size[0], SHIFT_GREEN);

            color_t color_ = get_floor_color(
                context, floor_pixels, floor_pitch,
                x, y, half_height
            );

            color_t r = (((color & 0xFF000000) >> 24) * 0.5 + ((color_ & 0xFF000000) >> 24) * 1.5) / 2;
            color_t g = (((color & 0x00FF0000) >> 16) * 0.5 + ((color_ & 0x00FF0000) >> 16) * 1.5) / 2;
            color_t b = (((color & 0x0000FF00) >> 8 ) * 0.5 + ((color_ & 0x0000FF00) >> 8)  * 1.5) / 2;

            color = r << 24 | g << 16 | b << 8 | 0XFF;

            pixels[y * (surface->pitch / 4) + x] = color;

        }
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(context->ren, surface);
    SDL_UnlockSurface(surface);

    SDL_RenderCopy(context->ren, texture, 0, 0);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return;
}
