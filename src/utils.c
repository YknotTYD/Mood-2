//utils.c

#include "../include/main.h"

void init_context(context_t *context, int screen_size[2])
{
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    context->font = TTF_OpenFont("assets/fonts/SourceCodePro-Medium.ttf", 30);
    
    context->win = SDL_CreateWindow("Mood-2", 100, 75, UNPACK2(screen_size), SDL_WINDOW_SHOWN);
    context->ren = SDL_CreateRenderer(context->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(context->ren, SDL_BLENDMODE_BLEND);
    context->quit = 0;

    context->screen_size[0] = screen_size[0];
    context->screen_size[1] = screen_size[1];

    for (int i = 0; i < FPS; i++) {
        context->frames[i] = 1;
    }

    context->line_count = 3;
    context->sprite_count = 2;
    context->lines = malloc(sizeof(int *) * 4 * context->line_count);
    context->line_indices = malloc(sizeof(int) * context->line_count);
    context->sprites = malloc(sizeof(SDL_Surface *) * context->sprite_count);

    SDL_Surface *temp = IMG_Load("assets/sprites/wall.png");
    context->sprites[0] = SDL_CreateTextureFromSurface(context->ren, temp);
    SDL_FreeSurface(temp);

    temp = IMG_Load("assets/sprites/otherwall.png");
    context->sprites[1] = SDL_CreateTextureFromSurface(context->ren, temp);
    SDL_FreeSurface(temp);

    context->line_indices[0] = 0;
    context->lines[0] = 200;
    context->lines[1] = 200;
    context->lines[2] = 200;
    context->lines[3] = 400;

    context->line_indices[1] = 1;
    context->lines[4] = 200;
    context->lines[5] = 400;
    context->lines[6] = 400;
    context->lines[7] = 400;

    context->line_indices[2] = 0;
    context->lines[8] = 400;
    context->lines[9] = 400;
    context->lines[10] = 400;
    context->lines[11] = 200;

    return;
}

void update_fps(context_t *context, long double frame_fps)
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

void display_fps(context_t *context)
{
    int width;
    int height;
    char *fpsstr = get_fpsstr(context);

    SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(context->font, fpsstr,
        (SDL_Color){255, 255, 255, 255}, context->screen_size[0] - 10);
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
