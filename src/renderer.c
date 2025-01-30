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

static void load_intersect(
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
    int lineindex, int ray_index, long double ray_angle
) {
    int height;

    norm *= cos(context->player->angle - ray_angle);
    height = WALLHEIGHT / norm;

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

static void process_color(context_t *context, int p0[2], long double p1[2])
{
    long double vect[2] = {p1[0] - p0[0], p1[1] - p0[1]};
    long double norm = sqrt(square(vect[0]) + square(vect[1]));

    norm *= 4.0;
    norm = (int)norm % 255;

    SDL_SetRenderDrawColor(context->ren, norm, 255 - norm, 0, 255);

    return;
}

static void launch_ray(
    int ray[4], context_t *context,
    int ray_index, long double ray_angle
) {
    int *lines = context->lines;
    int line_count = context->line_count;

    long double intersect[2];
    long double norm = 0;
    long double normin = 1.0 / 0.0;
    long double mintersect[2] = {0.0 / 0.0, 0.0 / 0.0};
    int norminindex = -1;

    for (int i = 0; i < line_count; i++) {
        load_intersect(
            intersect,
            UNPACK4(ray),
            UNPACK4(LINE_INDEX(lines, i))
        );
        if (intersect[0] != intersect[0]) {
            continue;
        }
        norm = square(intersect[0] - ray[0]) + square(intersect[1] - ray[1]);
        if (norm >= normin) {
            continue;
        }
        normin = norm;
        norminindex = i;
        mintersect[0] = intersect[0];
        mintersect[1] = intersect[1];
    }

    if (norminindex == -1) {
        return;
    }

    process_color(context, LINE_INDEX(lines, norminindex), mintersect);
    process_ray(context, sqrt(normin), norminindex, ray_index, ray_angle);
    //SDL_SetRenderDrawColor(context->ren, 255, 0, 0, 255);
    //SDL_RenderDrawLine(context->ren, UNPACK2(mintersect), UNPACK2(context->player->pos));

    return;
}

void render(context_t *context)
{
    player_t *player = context->player;
    long double angle;
    double plane;
    int ray[4];

    SDL_SetRenderDrawColor(context->ren, 255, 255, 0, 255);

    for (int ray_index = 0; ray_index < player->ray_count; ray_index++) {

        ray[0] = player->pos[0];
        ray[1] = player->pos[1];
        ray[2] = player->pos[0] + cos(angle) * RAY_LEN;
        ray[3] = player->pos[1] + sin(angle) * RAY_LEN;

        plane = (2.0 * ray_index / (long double)(player->ray_count - 1) - 1.0);
        angle = player->angle + atan(plane * tan(DEG_TO_RAD(player->FOV) / 2.0));

        launch_ray(ray, context, ray_index, angle);
    }
    return;
}
