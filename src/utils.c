//utils.c

#include "../include/main.h"

void init_context(context_t *context, int screen_size[2])
{
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    context->font = TTF_OpenFont("assets/fonts/SourceCodePro-Medium.ttf", 30);
    
    context->win = SDL_CreateWindow("Mood-2", 100, 75, UNPACK2(screen_size), SDL_WINDOW_SHOWN);
    context->ren = SDL_CreateRenderer(context->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    context->quit = 0;

    SDL_SetRenderDrawBlendMode(context->ren, SDL_BLENDMODE_BLEND);
    SDL_ShowCursor(SDL_DISABLE);

    context->screen_size[0] = screen_size[0];
    context->screen_size[1] = screen_size[1];

    for (int i = 0; i < FPS; i++) {
        context->frames[i] = 1;
    }
    for (int i = 0; i < 4; i++) {
        context->mouse_pos[i] = 0;
    }
    context->vel[0] = 0;
    context->vel[1] = 0;

    context->line_count = 7;
    context->sprite_count = 4;
    context->lines = malloc(sizeof(line_t) * context->line_count);
    context->sprites = malloc(sizeof(sprite_t) * context->sprite_count);

    SDL_Surface *temp = IMG_Load("assets/sprites/wall.png");
    context->sprites[0].texture = SDL_CreateTextureFromSurface(context->ren, temp);
    SDL_QueryTexture(context->sprites[0].texture, 0, 0, &context->sprites[0].width, &context->sprites[0].height);
    SDL_FreeSurface(temp);

    temp = IMG_Load("assets/sprites/otherwall.png");
    context->sprites[1].texture = SDL_CreateTextureFromSurface(context->ren, temp);
    SDL_QueryTexture(context->sprites[1].texture, 0, 0, &context->sprites[1].width, &context->sprites[1].height);
    SDL_FreeSurface(temp);

    temp = IMG_Load("assets/sprites/elsewall.png");
    context->sprites[2].texture = SDL_CreateTextureFromSurface(context->ren, temp);
    SDL_QueryTexture(context->sprites[2].texture, 0, 0, &context->sprites[2].width, &context->sprites[2].height);
    SDL_FreeSurface(temp);

    temp = IMG_Load("assets/sprites/alido.png");
    context->sprites[3].texture = SDL_CreateTextureFromSurface(context->ren, temp);
    SDL_QueryTexture(context->sprites[3].texture, 0, 0, &context->sprites[3].width, &context->sprites[3].height);
    SDL_FreeSurface(temp);

    context->lines[0].index = 0;
    context->lines[0].points[0] = 200;
    context->lines[0].points[1] = 200;
    context->lines[0].points[2] = 200;
    context->lines[0].points[3] = 400;

    context->lines[1].index = 1;
    context->lines[1].points[0] = 200;
    context->lines[1].points[1] = 400;
    context->lines[1].points[2] = 400;
    context->lines[1].points[3] = 400;

    context->lines[2].index = 0;
    context->lines[2].points[0] = 400;
    context->lines[2].points[1] = 400;
    context->lines[2].points[2] = 400;
    context->lines[2].points[3] = 200;

    context->lines[3].index = 2;
    context->lines[3].points[0] = 400;
    context->lines[3].points[1] = 200;
    context->lines[3].points[2] = 600;
    context->lines[3].points[3] = 300;

    context->lines[4].index = 3;
    context->lines[4].points[0] = 5000;
    context->lines[4].points[1] = 5000;
    context->lines[4].points[2] = 4800;
    context->lines[4].points[3] = 4800;

    context->lines[5].index = 0;
    context->lines[5].points[0] = 500;
    context->lines[5].points[1] = 500;
    context->lines[5].points[2] = 500;
    context->lines[5].points[3] = 1500;

    context->lines[6].index = 0;
    context->lines[6].points[0] = 600;
    context->lines[6].points[1] = 500;
    context->lines[6].points[2] = 600;
    context->lines[6].points[3] = 1500;

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

void update_vel(context_t *context)
{
    SDL_GetMouseState(&context->mouse_pos[0], &context->mouse_pos[1]);

    context->vel[0] = context->mouse_pos[0] - context->screen_size[0] / 2;
    context->vel[1] = context->mouse_pos[1] - context->screen_size[1] / 2;

    SDL_WarpMouseInWindow(
        context->win,
        context->screen_size[0] / 2,
        context->screen_size[1] / 2
    );

    return;
}
