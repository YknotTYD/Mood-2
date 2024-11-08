//render.c

#include "mood_2.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static int delta_cmp(long double n, long double delta)
{
    if (delta > 0) {
        return n >= 0 && n <= delta;
    }
    return n <= 0 && n >= delta;
}

static void load_intersection(long double intersect[2],
                              int x1, int y1, int x2, int y2,
                              int x3, int y3, int x4, int y4)
{
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

static void launch_ray(long double intersect[2], int ray[2], Map *map)
{

    load_intersection(intersect, ray[0], ray[1], ray[2], ray[3], 
                      map->lines[0][0], map->lines[0][1], map->lines[0][2], map->lines[0][3]);
    return;
}

void RenderRays(FrameBuffer *fbuffer, Player *player, Map *map)
{
    long double angle = player->angle - player->FOV/2 * 0;
    int ray[4];
    long double intersect[2];

    for (int i = 0; i < player->ray_count; i++) {

        ray[0] = player->pos[0];
        ray[1] = player->pos[1];
        ray[2] = player->pos[0] + cos(angle) * 600;
        ray[3] = player->pos[1] + sin(angle) * 600;

        draw_line(fbuffer, (int[2]){ray[0], ray[1]},
                           (int[2]){ray[2], ray[3]},
                  (char[4]){122, 122, 122, 255});

        launch_ray(intersect, ray, map);

        draw_circle(fbuffer, (int)intersect[0], (int)intersect[1], 22, (char[4]){0, 0, 255, 255});
        angle += player->ray_step;
        break;
    }

    return;
}
