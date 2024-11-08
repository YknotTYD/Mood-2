//map.c

#include "mood_2.h"
#include <stdlib.h>

Map *new_map()
{
    Map *map = malloc(sizeof(Map));
    map->line_count = 2;

    map->lines = malloc(sizeof(int) * map->line_count);

    for (int i = 0; i < map->line_count; i++) {
        map->lines[i] = malloc(sizeof(int) * 4);
    }

    map->lines[0][0] = 22;
    map->lines[0][1] = 22;
    map->lines[0][2] = 122;
    map->lines[0][3] = 345;

    map->lines[1][0] = 456;
    map->lines[1][1] = 82;
    map->lines[1][2] = 0;
    map->lines[1][3] = 345;

    return map;
}

void display_map(Map *map, FrameBuffer *fbuffer)
{
    for (int i = 0; i < map->line_count; i++) {
        draw_line(fbuffer, (int[2]){map->lines[i][0], map->lines[i][1]},
                           (int[2]){map->lines[i][2], map->lines[i][3]},
                  (char[4]){255, 255, 0, 255});
    }
    return;
}
