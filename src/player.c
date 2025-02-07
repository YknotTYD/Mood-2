//player.c

#include "../include/main.h"

static void cache_rays(player_t *player)
{
    long double plane;
    long double half_fov = DEG_TO_RAD(player->FOV) / 2.0;

    player->angles = malloc(sizeof(long double) * player->ray_count);

    for (int i = 0; i < player->ray_count; i++) {
        plane = (2.0 * i / (player->ray_count + 1)) - 1.0;
        player->angles[i] = atan(plane * tan(half_fov));
    }

    return;
}

void init_player(player_t **player, int ray_count)
{
    *player = malloc(sizeof(player_t));

    (*player)->pos[0] = 352;
    (*player)->pos[1] = 352;
    (*player)->z = 0;
    (*player)->angle = 3;
    (*player)->FOV = 90;
    (*player)->ray_count = ray_count;
    (*player)->ray_step = DEG_TO_RAD((*player)->FOV) /
        (long double)(*player)->ray_count;

    cache_rays(*player);

    return;
}

void render_player(context_t *context)
{
    int dx;
    int dy;

    SDL_SetRenderDrawColor(context->ren, 0, 0, 255, 255);

    for (int w = 0; w < PLAYER_RADIUS * 2; w++) {
        for (int h = 0; h < PLAYER_RADIUS * 2; h++) {

            dx = PLAYER_RADIUS - w;
            dy = PLAYER_RADIUS - h;

            if ((dx*dx + dy*dy) > (PLAYER_RADIUS * PLAYER_RADIUS)) {
                continue;
            }

            SDL_RenderDrawPoint(
                context->ren,
                context->player->pos[0] + dx,
                context->player->pos[1] + dy
            );
        }
    }

    SDL_RenderDrawLine(
        context->ren,
        UNPACK2(context->player->pos),
        context->player->pos[0] + cos(context->player->angle) * 1e+4,
        context->player->pos[1] + sin(context->player->angle) * 1e+4
    );

    return;
}

void render_lines(context_t *context)
{
    SDL_SetRenderDrawColor(context->ren, 0, 255, 0, 255);

    for (int i = 0; i < context->line_count; i++) {
        SDL_RenderDrawLine(context->ren, UNPACK4(context->lines[i].points));
    }

    return;
}

static void slide_player(
    context_t *context, line_t *line,
    long double pos[2], long double aim[2]
) {
    long double linorm;
    long double scal;

    long double player_vect[2] = {aim[0] - pos[0], aim[1] - pos[1]};
    long double line_vect[2] = {
        line->points[0] - line->points[2],
        line->points[1] - line->points[3]
    };

    linorm = sqrt(SQUARE(line_vect[0]) + SQUARE(line_vect[1]));
    
    line_vect[0] /= linorm;
    line_vect[1] /= linorm;

    scal = player_vect[0] * line_vect[0] + player_vect[1] * line_vect[1];

    context->player->pos[0] += line_vect[0] * scal;
    context->player->pos[1] += line_vect[1] * scal;

    return;
}

static void player_collide(context_t *context, long double vect[2])
{
    long double ray[4];
    long double intersect[2];
    long double norm;
    line_t *line;
    long double original_pos[2] = {UNPACK2(context->player->pos)};

    ray[0] = context->player->pos[0];
    ray[1] = context->player->pos[1];
    ray[2] = context->player->pos[0] + vect[0] * PLAYER_SPEED;
    ray[3] = context->player->pos[1] + vect[1] * PLAYER_SPEED;

    launch_ray(context, ray, intersect, &norm, &line);

    if (intersect[0] != intersect[0]) {
        context->player->pos[0] = ray[2];
        context->player->pos[1] = ray[3];
        return;
    }

    slide_player(context, line, intersect, ray + 2);

    ray[0] = original_pos[0];
    ray[1] = original_pos[1];
    ray[2] = context->player->pos[0];
    ray[3] = context->player->pos[1];
    
    launch_ray(context, ray, intersect, &norm, &line);
    
    if (intersect[0] != intersect[0]) {
        return;
    }
    
    slide_player(context, line, intersect, ray + 2);
    
    ray[0] = original_pos[0];
    ray[1] = original_pos[1];
    ray[2] = context->player->pos[0];
    ray[3] = context->player->pos[1];
    
    launch_ray(context, ray, intersect, &norm, &line);
    if (intersect[0] == intersect[0]) {
        context->player->pos[0] = original_pos[0];
        context->player->pos[1] = original_pos[1];
    }

    return;
}

static void update_player_pos(context_t *context, const unsigned char *keyboard)
{
    long double vect[2];
    int key_vect[2]={
        keyboard[SDL_SCANCODE_D] - keyboard[SDL_SCANCODE_A],
        keyboard[SDL_SCANCODE_W] - keyboard[SDL_SCANCODE_S]
    };

    vect[0] = cos(context->player->angle) * key_vect[1];
    vect[1] = sin(context->player->angle) * key_vect[1];

    context->player->angle += PI / 2.0;

    vect[0] += cos(context->player->angle) * key_vect[0];
    vect[1] += sin(context->player->angle) * key_vect[0];

    context->player->angle -= PI / 2.0;

    player_collide(context, vect);

    return;
}

void update_player(context_t *context, long double clock)
{
    const unsigned char *keyboard = SDL_GetKeyboardState(0);
    long double vect[2] = {UNPACK2(context->player->pos)};

    context->player->angle += context->vel[0] * PLAYER_ANGULAR_SPEED;
    update_player_pos(context, keyboard);

    vect[0] -= context->player->pos[0];
    vect[1] -= context->player->pos[1];

    (void)clock;
    if (vect[0] || vect[1]){
        //context->player->z = (sin(clock * PLAYER_STEP_SPEED) + 1.0) * PLAYER_STEP_HEIGHT;
        return;
    }

    //context->player->z *= 0.8;

    return;
}
