//main.h

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#ifndef MAIN_HEADER

    #define MAIN_HEADER
    #define UNPACK2(arr) arr[0], arr[1]
    #define UNPACK4(arr) (arr)[0], (arr)[1], (arr)[2], (arr)[3]
    #define NOW (clock()/(double)CLOCKS_PER_SEC)
    #define LINE_INDEX(lines, n) (&(lines)[((n) * 4)])
    #define PI 3.1415926535897932384626433832795028841L
    #define DEG_TO_RAD(angle) (((angle) / 180.0) * PI)
    #define ABS(n) ((n) > 0 ? (n): -(n))
    #define PLAYER_RADIUS 10
    #define PLAYER_SPEED 7
    #define PLAYER_ANGULAR_SPEED 0.06
    #define RAY_LEN 1e+5
    #define WALLHEIGHT 21000
    #define FPS 120

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
    TTF_Font *font;
    int *lines;
    int *line_indices;
    SDL_Texture **sprites;
    int line_count;
    int sprite_count;
    int quit;
    int screen_size[2];
    long double frames[FPS];
} context_t;

void init_context(context_t *context,int screen_size[2]);
void update_fps(context_t *context, long double frame_fps);
void display_fps(context_t *context);

void init_player(player_t **player, int ray_count);
void render_player(context_t *context);
void render_lines(context_t *context);
void update_player(context_t *context);

void render(context_t *context);

#endif
