//player.c

#include "../include/main.h"

void init_player(player_t **player, int ray_count)
{
    *player = malloc(sizeof(player_t));
    (*player)->pos[0] = 222;
    (*player)->pos[1] = 222;
    (*player)->angle = 3;
    (*player)->FOV = 120;
    (*player)->ray_count = ray_count;
    (*player)->ray_step = DEG_TO_RAD((*player)->FOV) /
        (long double)(*player)->ray_count;
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
        SDL_RenderDrawLine(context->ren, UNPACK4(LINE_INDEX(context->lines, i)));
    }

    return;
}

static void update_player_pos(player_t *player, const unsigned char *keyboard)
{
    long double vect[2]={
        keyboard[SDL_SCANCODE_D] - keyboard[SDL_SCANCODE_A],
        keyboard[SDL_SCANCODE_W] - keyboard[SDL_SCANCODE_S]
    };

    player->pos[0] += cos(player->angle) * vect[1] * PLAYER_SPEED;
    player->pos[1] += sin(player->angle) * vect[1] * PLAYER_SPEED;

    player->angle += 3.1415926535897932384626433832795028841 / 2.0;

    player->pos[0] += cos(player->angle) * vect[0] * PLAYER_SPEED;
    player->pos[1] += sin(player->angle) * vect[0] * PLAYER_SPEED;

    player->angle -= 3.1415926535897932384626433832795028841 / 2.0;

    return;

}

static void update_player_angle(player_t *player, const unsigned char *keyboard)
{
    long double vect = keyboard[SDL_SCANCODE_RIGHT] - keyboard[SDL_SCANCODE_LEFT];
    player->angle += vect * PLAYER_ANGULAR_SPEED;

    return;
}

void update_player(context_t *context)
{
    const unsigned char *keyboard = SDL_GetKeyboardState(0);
    player_t *player = context->player;

    
    update_player_angle(player, keyboard);
    update_player_pos(player, keyboard);
    return;
}
