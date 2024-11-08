//map.c

#include "mood_2.h"
#include <stdlib.h>
#include <unistd.h>

Map *new_map()
{
    Map *map = malloc(sizeof(Map));

    map->line_count = 20;
    map->lines = malloc(sizeof(int) * map->line_count * map->line_count);

    for (int i = 0; i < map->line_count; i++) {
        map->lines[i] = malloc(sizeof(int) * 4);
    }

    map->lines[0][0] = 1024;map->lines[0][1] = 493;map->lines[0][2] = 1095;map->lines[0][3] = 635;
    map->lines[1][0] = 728;map->lines[1][1] = 210;map->lines[1][2] = 935;map->lines[1][3] = 662;
    map->lines[2][0] = 1126;map->lines[2][1] = 280;map->lines[2][2] = 267;map->lines[2][3] = 496;
    map->lines[3][0] = 913;map->lines[3][1] = 447;map->lines[3][2] = 231;map->lines[3][3] = 124;
    map->lines[4][0] = 1014;map->lines[4][1] = 489;map->lines[4][2] = 39;map->lines[4][3] = 40;
    map->lines[5][0] = 227;map->lines[5][1] = 562;map->lines[5][2] = 1407;map->lines[5][3] = 136;
    map->lines[6][0] = 807;map->lines[6][1] = 640;map->lines[6][2] = 29;map->lines[6][3] = 106;
    map->lines[7][0] = 508;map->lines[7][1] = 57;map->lines[7][2] = 1408;map->lines[7][3] = 196;
    map->lines[8][0] = 999;map->lines[8][1] = 450;map->lines[8][2] = 1199;map->lines[8][3] = 288;
    map->lines[9][0] = 1161;map->lines[9][1] = 384;map->lines[9][2] = 480;map->lines[9][3] = 563;
    map->lines[10][0] = 704;map->lines[10][1] = 436;map->lines[10][2] = 1075;map->lines[10][3] = 623;
    map->lines[11][0] = 57;map->lines[11][1] = 491;map->lines[11][2] = 967;map->lines[11][3] = 398;
    map->lines[12][0] = 865;map->lines[12][1] = 355;map->lines[12][2] = 589;map->lines[12][3] = 397;
    map->lines[13][0] = 409;map->lines[13][1] = 504;map->lines[13][2] = 744;map->lines[13][3] = 318;
    map->lines[14][0] = 168;map->lines[14][1] = 690;map->lines[14][2] = 1253;map->lines[14][3] = 387;
    map->lines[15][0] = 758;map->lines[15][1] = 619;map->lines[15][2] = 610;map->lines[15][3] = 368;
    map->lines[16][0] = 1067;map->lines[16][1] = 282;map->lines[16][2] = 361;map->lines[16][3] = 191;
    map->lines[17][0] = 776;map->lines[17][1] = 677;map->lines[17][2] = 686;map->lines[17][3] = 174;
    map->lines[18][0] = 597;map->lines[18][1] = 629;map->lines[18][2] = 830;map->lines[18][3] = 231;
    map->lines[19][0] = 617;map->lines[19][1] = 670;map->lines[19][2] = 1280;map->lines[19][3] = 486;

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
