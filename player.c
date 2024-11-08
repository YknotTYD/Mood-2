//player.c

#include "mood_2.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void display_player(Player *player, FrameBuffer *fbuffer)
{
    long double angle = player->angle - player->FOV/2 * 0;

    for (int i = 0; i < player->ray_count; i++) {
        draw_line(fbuffer, (int[2]){player->pos[0], player->pos[1]},
            (int[2]){player->pos[0] + cos(angle) * 500,
            player->pos[1] + sin(angle) * 500},
                  (char[4]){0, 255, 0, 255});
        angle += player->ray_step;
        break;
    }
    
    draw_circle(fbuffer, player->pos[0], player->pos[1], 20, (char[4]){255, 0, 0, 255});

    return;
}

Player *new_player(long double x, long double y, long double speed, int FOV, int ray_count)
{
    Player *player = malloc(sizeof(Player));

    player->angle = 0;
    player->FOV = FOV;
    player->ray_count = ray_count;
    player->ray_step = (FOV / (long double)(ray_count * 180)) * 3.1415926535897932384626433832795028841L;

    player->pos[0] = x;
    player->pos[1] = y;

    player->speed = speed;

    return player;
}

static void MovePlayerDir(Player *player, int movect) {

    long double vect[2] = {cos(player->angle), sin(player->angle)};

    player->pos[0] += movect * vect[0] * player->speed;
    player->pos[1] += movect * vect[1] * player->speed;

    return;
}
void UpdatePlayer(Player *player, int movect[2], long double angle_offset)
{

    player->angle += angle_offset;

    MovePlayerDir(player, movect[1]);
    player->angle -= 3.1415926535897932384626433832795028841L/2.0L;
    MovePlayerDir(player, movect[0]);
    player->angle += 3.1415926535897932384626433832795028841L/2.0L;

    return;
}
