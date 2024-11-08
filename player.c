//player.c

#include "mood_2.h"
#include <stdlib.h>
#include <math.h>

void display_player(Player *player, FrameBuffer *fbuffer)
{
    draw_circle(fbuffer, player->pos[0], player->pos[1], 20, player->color);
    draw_line(fbuffer, player->pos, (int[2]){player->pos[0] + cos(player->angle) * 500,
                                             player->pos[1] + sin(player->angle) * 500},
              player->color);
    return;
}

Player *new_player(int x, int y, char color[4])
{
    Player *player = malloc(sizeof(Player));

    player->angle = 0;

    player->pos[0] = x;
    player->pos[1] = y;

    for (int i = 0; i < 4; i++) {
        player->color[i] = color[i];
    }

    return player;
}
