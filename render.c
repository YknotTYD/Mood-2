//render.c

#include "mood_2.h"
#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <stdio.h>

//wall above screen
//s or t test first if player ray (12239283928329 norm)

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

static int launch_ray(long double intersect[2], int ray[4], Map *map, int *line_index)
{
    long double newtersect[2];
    long double norm;
    long double normin = 1.0/0.0;

    for (int i = 0; i < map->line_count; i++) {
    
        load_intersection(newtersect, ray[0], ray[1], ray[2], ray[3], 
            map->lines[i][0], map->lines[i][1], map->lines[i][2], map->lines[i][3]);

        if (newtersect[0] != newtersect[0]) {
            continue;
        }
            
        norm = square(newtersect[0] - ray[0]) + square(newtersect[1] - ray[1]);

        if (norm < normin) {
            normin = norm;
            intersect[0] = newtersect[0];
            intersect[1] = newtersect[1];
            *line_index = i;
        }
    }
    return normin;
}

static void render_ray(sfRenderWindow *window, long double norm, int i, int ray_hit, int wall_height, int screen_size[2], Map *map)
{

    int height = wall_height/norm;

    norm = (height/(long double)screen_size[1])*255;
    norm = norm > 255 ? 255 : norm;
    norm = norm < 0 ? 0 : norm;

    /*draw_line(fbuffer, (int[2]){i, (screen_size[1]-height)/2.0},
                       (int[2]){i, screen_size[1]/2.0+height/2.0},
                  (char[4]){122, norm, norm, 255});*/

    sfSprite_setPosition(map->texture->cuts[ray_hit], (sfVector2f){i, (screen_size[1] - height) / 2.0});
    sfSprite_setScale(map->texture->cuts[ray_hit], (sfVector2f){1, height / (long double)map->texture->width});
    sfRenderWindow_drawSprite(window, map->texture->cuts[ray_hit], NULL);

    return;
}

void RenderRays(sfRenderWindow *window, Player *player, Map *map, int screen_size[2])
{
    long double angle = player->angle - player->FOV/2.0;
    int ray[4];
    long double intersect[2];
    long double norm;
    int line_index;
    int temptrash;

    for (int i = 0; i < player->ray_count; i++) {

        intersect[0] = cos(player->angle) / 1.0;
        intersect[1] = sin(player->angle) / 1.0;

        intersect[0] += cos(player->angle + 3.14159265/2.0) * ((i - player->ray_count/2.0) / (long double)(player->ray_count));
        intersect[1] += sin(player->angle + 3.14159265/2.0) * ((i - player->ray_count/2.0) / (long double)(player->ray_count));

        intersect[0] *= 12000;
        intersect[1] *= 12000;

        intersect[0] += player->pos[0];
        intersect[1] += player->pos[1];
    
        ray[0] = player->pos[0];
        ray[1] = player->pos[1];
        ray[2] = intersect[0];
        ray[3] = intersect[1];

        angle += player->ray_step;
        norm = launch_ray(intersect, ray, map, &line_index);

        if (norm > norm) {
            continue;
        }

        norm = sqrt(norm);// * cos((player->ray_count / 2.0 - i) / ((long double)player->ray_count/2.0) * player->FOV/2.0);

        temptrash = (sqrt(square(intersect[0] - map->lines[line_index][0]) + square(intersect[1] - map->lines[line_index][1])));
        temptrash %= map->texture->width;
        render_ray(window, sqrt(norm), i, temptrash, 3000 * 3, screen_size, map);
    }

    return;
}





