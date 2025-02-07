//main.c

#include "../include/main.h"
//#include <emscripten.h>

//free everything
//make the rendering use shaders
//use the ray hit angle to add shade
//normalize player movements
//make a level editor
//add enemies with pathfinding
//add basic shadows?
//add the ability to look up and down
//stop mouse grab when not focused
//find the correct value for RENDER_NORMULT
//make the steps affect far away walls less somehow?
//load walls from some file
//add everything on screen at once
//don't create and destroy the mode7 surface each frame
//add a mode7

static int screen_size[2]={1650, 900};
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

static void main_loop(context_t *context)
{
    double frame_start = NOW;

    update_vel(context);
    update_player(context, NOW);

    SDL_SetRenderDrawColor(context->ren, 0, 0, 0, 255);
    SDL_RenderClear(context->ren);

    render_floor(context);
    render_walls(context);
    display_fps(context);

    SDL_RenderPresent(context->ren);

    update_fps(context, 1/(NOW - frame_start));
    while (NOW - frame_start < 1 / (double)FPS);
    poll_quit();

    return;
}

int main(int argc, char **argv)
{
    init_context(&context, screen_size);
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
