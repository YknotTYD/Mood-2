//renderer.c

#include "../include/main.h"

static long double min(long double a, long double b)
{
    if (a < b) {
        return a;
    }
    return b;
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
    long double x1, long double y1, long double x2, long double y2,
    long double x3, long double y3, long double x4, long double y4
) {
    long double a = x2 - x1;
    long double b = x4 - x3;
    long double c = x3 - x1;
    long double d = y2 - y1;
    long double e = y4 - y3;
    long double f = y3 - y1;

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
    int ray_index, long double ray_angle,
    long double intersect[2], line_t *line
) {
    long double vect[2] = {line->points[0] - intersect[0], line->points[1] - intersect[1]};
    long double relnorm = sqrt(SQUARE(vect[0]) + SQUARE(vect[1]));
    sprite_t *sprite = &context->sprites[line->index];
    int height;

    norm *= cos(context->player->angle - ray_angle);
    height = WALLHEIGHT / norm;

    SDL_RenderCopy(
        context->ren,
        sprite->texture,
        &(SDL_Rect){((int)(relnorm * RENDER_NORMULT)) % sprite->width, 0, 1, sprite->height},
        &(SDL_Rect){
            ray_index,
            context->screen_size[1] / 2.0 - height - context->player->z * min(1, (500 / norm)),
            1,
            height * 2.0 + 1}
    );

    return;
}

void launch_ray(
    context_t *context, long double ray[4],
    long double mintersect[2], long double *normin, line_t **minline
) {
    long double intersect[2];
    long double norm = 0;
    int norminindex = -1;

    mintersect[0] = 0.0 / 0.0;
    mintersect[1] = 0.0 / 0.0;
    *normin = 1.0 / 0.0;

    for (int i = 0; i < context->line_count; i++) {
        load_intersect(
            intersect,
            UNPACK4(ray),
            UNPACK4(context->lines[i].points)
        );
        if (intersect[0] != intersect[0]) {
            continue;
        }
        norm = SQUARE(intersect[0] - ray[0]) + SQUARE(intersect[1] - ray[1]);
        if (norm >= *normin) {
            continue;
        }
        *normin = norm;
        norminindex = i;
        mintersect[0] = intersect[0];
        mintersect[1] = intersect[1];
    }

    if (norminindex == -1) {
        return;
    }

    *normin = sqrt(*normin);    *minline = &context->lines[norminindex];
    *minline = &context->lines[norminindex];

    return;
}

void render_walls(context_t *context)
{
    player_t *player = context->player;
    long double angle;
    long double ray[4];

    long double intersect[2];
    long double norm;
    line_t *line;

    for (int ray_index = 0; ray_index < player->ray_count; ray_index++) {

        angle = player->angle + player->angles[ray_index];

        ray[0] = player->pos[0];
        ray[1] = player->pos[1];
        ray[2] = player->pos[0] + cosl(angle) * RAY_LEN;
        ray[3] = player->pos[1] + sinl(angle) * RAY_LEN;

        launch_ray(
            context, ray,
            intersect, &norm, &line
        );

        if (intersect[0] != intersect[0]) {
            continue;
        }

        process_ray(
            context, norm, ray_index,
            angle, intersect, line
        );

    }
    return;
}
