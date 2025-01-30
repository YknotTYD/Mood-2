//main.c

#include "../include/main.h"
//#include <emscripten.h>

//display FPS
//cache every (ray/render)related cacheable thing
//make the rendering use shaders
//use the ray hit angle to add shade

static double FPS = 120.0;
static int screen_size[2]={1650, 900};
//static const unsigned char *keyboard;
static context_t context;

static int poll_quit(void)
{
    while (SDL_PollEvent(&context.events)) {
        if (context.events.type == SDL_QUIT) {
            context.quit = 1;
            return 0;
        }
    }
    return 1;
}

static void init_context(context_t *context)
{
    context->win = SDL_CreateWindow("Mood-2", 100, 75, UNPACK2(screen_size), SDL_WINDOW_SHOWN);
    context->ren = SDL_CreateRenderer(context->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    context->quit = 0;

    context->screen_size[0] = screen_size[0];
    context->screen_size[1] = screen_size[1];

    context->line_count = 3;
    context->lines = malloc(sizeof(int *) * 4 * context->line_count);

    context->lines[0] = 200;
    context->lines[1] = 200;
    context->lines[2] = 200;
    context->lines[3] = 400;

    context->lines[4] = 200;
    context->lines[5] = 400;
    context->lines[6] = 400;
    context->lines[7] = 400;

    context->lines[8] = 400;
    context->lines[9] = 400;
    context->lines[10] = 400;
    context->lines[11] = 200;

    return;
}

static void main_loop(context_t *context)
{
    double frame_start = NOW;

    update_player(context);

    SDL_SetRenderDrawColor(context->ren, 0, 0, 0, 255);
    SDL_RenderClear(context->ren);

    render(context);
    //render_player(context);
    //render_lines(context);

    SDL_RenderPresent(context->ren);

    while (NOW - frame_start < 1 / FPS);
    poll_quit();

    return;
}

int main(int argc, char **argv)
{
    init_context(&context);
    init_player(&context.player, screen_size[0]);

    (void)argc;
    (void)argv;
    //emscripten_set_main_loop_args(main_loop, &context, -1, 1);
    while (context.quit == 0) {
        main_loop(&context);
    }

    SDL_DestroyRenderer(context.ren);
    SDL_DestroyWindow(context.win);
    SDL_Quit();

    return 0;
}
