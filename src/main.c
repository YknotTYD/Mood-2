//main.c

#include "../include/main.h"
//#include <emscripten.h>

//display FPS
//cache every (ray/render)related cacheable thing
//make the rendering use shaders
//use the ray hit angle to add shade
//add a README
//put everything into more files
//clean up everything

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
    TTF_Init();
    context->font = TTF_OpenFont("assets/fonts/SourceCodePro-Medium.ttf", 30);

    context->win = SDL_CreateWindow("Mood-2", 100, 75, UNPACK2(screen_size), SDL_WINDOW_SHOWN);
    context->ren = SDL_CreateRenderer(context->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    context->quit = 0;

    context->screen_size[0] = screen_size[0];
    context->screen_size[1] = screen_size[1];

    for (int i = 0; i < FPS; i++) {
        context->frames[i] = 1;
    }

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

static void update_fps(context_t *context, long double frame_fps)
{
    long double temp;

    for (int i = 0; i < FPS - 1; i++) {
        temp = context->frames[i];
        context->frames[i] = context->frames[i + 1];
        context->frames[i + 1] = temp;
    }
    context->frames[FPS - 1] = frame_fps;
    return;
}

static char *int_to_str(int nbr)
{
    int start = 0;
    int end;
    char *str = malloc(64);
    char temp;
    int i = 0;

    do {
        str[i] = '0' + (nbr % 10);
        i++;
        nbr /= 10;
    } while (nbr);
    str[i] = '\0';
    end = i - 1;
    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}


static char *get_fpsstr(context_t *context)
{
    char *fpsstr;
    double fps = 0;

    for (int i = 0; i < FPS; i++) {
        fps += context->frames[i];
    }
    fps /= FPS;

    fpsstr = int_to_str(fps);
    return fpsstr;
}

static void display_fps(context_t *context)
{
    int width;
    int height;
    char *fpsstr = get_fpsstr(context);

    SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(context->font, fpsstr,
        (SDL_Color){255, 255, 255, 255}, screen_size[0] - 10);
    SDL_Texture *text = SDL_CreateTextureFromSurface(context->ren, surf);

    SDL_QueryTexture(text, 0, 0, &width, &height);

    SDL_RenderCopy(
        context->ren, text, 0,
        &(SDL_Rect){
        10, 10,
        width, height}
    );

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(text);

    return;
}

static void main_loop(context_t *context)
{
    double frame_start = NOW;

    update_player(context);

    SDL_SetRenderDrawColor(context->ren, 0, 0, 0, 255);
    SDL_RenderClear(context->ren);

    render(context);
    render_player(context);
    render_lines(context);
    display_fps(context);

    SDL_RenderPresent(context->ren);

    update_fps(context, 1/(NOW - frame_start));
    while (NOW - frame_start < 1 / (double)FPS);
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
