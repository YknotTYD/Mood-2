//renderer.c

#include "../include/main.h"

static long double square(const long double n)
{
    return n * n;
}

static int delta_cmp(long double n, long double delta)
{
    if (delta > 0) {
        return n >= 0 && n <= delta;
    }
    return n <= 0 && n >= delta;
}

static void load_intersection(
    long double intersect[2],
    int x1, int y1, int x2, int y2,
    int x3, int y3, int x4, int y4
) {
    int a = x2 - x1;
    int b = x4 - x3;
    int c = x3 - x1;
    int d = y2 - y1;
    int e = y4 - y3;
    int f = y3 - y1;

    long double delta = (a * e - d * b);
    long double s;
    long double t;

    intersect[0] = 0.0/0.0;
    intersect[1] = 0.0/0.0;

    s = (c * e - f * b);
    if (!delta_cmp(s, delta)){
        return;
    }

    t = (c * d - f * a);
    if (!delta_cmp(t, delta)){
        return;
    }

    intersect[0] = x1 + (s / delta) * a;
    intersect[1] = y1 + (s / delta) * d;

    return;
}

static void process_ray(
    context_t *context, long double norm,
    int lineindex, int ray_index
) {
    int height = 4200000 / norm;

    (void)lineindex;
    SDL_RenderDrawLine(
        context->ren,
        ray_index,
        context->screen_size[1] / 2 - height,
        ray_index,
        context->screen_size[1] / 2 + height
    );

    return;
}

static void launch_ray(
    int ray[4], context_t *context,
    long double intersection[2], int ray_index
) {
    int *lines = context->lines;
    int line_count = context->line_count;

    long double norm = 0;
    long double normin = 1.0 / 0.0;
    int norminindex = -1;

    for (int i = 0; i < line_count; i++) {

        load_intersection(
            intersection,
            UNPACK4(ray),
            UNPACK4(LINE_INDEX(lines, i))
        );

        norm = square(intersection[0] - ray[0]) + square(intersection[1] - ray[1]);

        if (norm >= normin) {
            continue;
        }

        normin = norm;
        norminindex = i;
    }

    if (norminindex == -1) {
        return;
    }

    process_ray(context, normin, norminindex, ray_index);

    return;
}

void render(context_t *context)
{
    player_t *player = context->player;
    long double angle = player->angle - player->ray_step * player->ray_count / 2;
    int ray[4];
    long double intersection[2];

    for (int ray_index = 0; ray_index < player->ray_count; ray_index++) {

        ray[0] = player->pos[0];
        ray[1] = player->pos[1];
        ray[2] = player->pos[0] + cos(angle) * RAY_LEN;
        ray[3] = player->pos[1] + sin(angle) * RAY_LEN;

        angle += player->ray_step;

        SDL_RenderDrawLine(
            context->ren,
            UNPACK4(ray)
        );

        SDL_SetRenderDrawColor(context->ren, 255, 255, 0, 255);
        launch_ray(
            ray, context,
            intersection, ray_index
        );
        SDL_RenderFillRect(
            context->ren,
            &(SDL_Rect){UNPACK2(intersection), 2, 2}
        );
        SDL_SetRenderDrawColor(context->ren, 0, 0, 255, 255);
    }
    return;
}








