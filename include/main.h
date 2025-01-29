//main.h

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#ifndef MAIN_HEADER
    #define MAIN_HEADER
    #define UNPACK2(arr) arr[0], arr[1]
    #define UNPACK4(arr) (arr)[0], (arr)[1], (arr)[2], (arr)[3]
    #define NOW (clock()/(double)CLOCKS_PER_SEC)
    #define PLAYER_RADIUS 10
    #define LINE_INDEX(lines, n) (&(lines)[((n) * sizeof(int) * 4)])
    #define PLAYER_SPEED 7
    #define PLAYER_ANGULAR_SPEED 0.07
    #define RAY_LEN 1e+5
    #define DEG_TO_RAD(angle) (((angle) / 180.0) * 3.1415926535897932384626433832795028841)

typedef struct {
    long double pos[2];
    long double angle;
    int FOV;
    int ray_count;
    long double ray_step;
} player_t;

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Event events;
    player_t *player;
    int *lines;
    int line_count;
    int quit;
} context_t;

void init_player(player_t **player);
void render_player(context_t *context);
void render_lines(context_t *context);
void update_player(context_t *context);

void render(context_t *context);

#endif
