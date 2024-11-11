//main.c

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Window/Keyboard.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "mood_2.h"
#include <stdio.h>

//draw fbuff
//put fbuff in text
//link text to sprite
//draw sprite on window
//flip
//
//sfKeyboard_isKeyPressed
//sfKey<key>

//Multi(threading/processing)
//Rooms
//store cos sin etc...
//display fps
//add transparency
//add light?
//remove framebuffer update

FrameBuffer *new_frame_buffer(int width, int height)
{
    FrameBuffer *fbuffer = malloc(sizeof(FrameBuffer));

    fbuffer->pixels = malloc(32*width*height);
    fbuffer->width = width;
    fbuffer->height = height;

    fbuffer->size[0] = width;
    fbuffer->size[1] = height;

    return fbuffer;
}

void clear_buffer(FrameBuffer *fbuffer)
{
    memset((fbuffer->pixels), 0, (fbuffer->width*fbuffer->height*32));
}

void display_brick_column(sfRenderWindow *window, sfSprite **sprites, int col_index, int x, int height)
{
    sfSprite_setPosition(sprites[col_index], (sfVector2f){col_index, x});
    sfSprite_setScale(sprites[col_index], (sfVector2f){1, height});
    sfRenderWindow_drawSprite(window, sprites[col_index], 0);
}

int main()
{
    int screen_size[2]={1500, 700};

    Player *player = new_player(0, 200, 5, 120, screen_size[0]);
    Map *map = new_map();

    sfVideoMode mode = {screen_size[0], screen_size[1], 32};
    sfRenderWindow* window;
    //sfWindow *mposwin;
    sfTexture* texture;
    sfSprite* sprite; 
    //FrameBuffer *fbuffer;
    sfEvent event;
    //int mouse_pos[2] = sfMouse_getPosition(window);

    window = sfRenderWindow_create(mode, "Mood 2", sfResize | sfClose, NULL);
    //mposwin = sfWindow_create(mode, "Mood 2", sfResize | sfClose, NULL);
    //fbuffer = new_frame_buffer(screen_size[0], screen_size[1]);
    texture = sfTexture_create(screen_size[0], screen_size[1]);
    sprite = sfSprite_create();

    srand(time(NULL));

    while (sfRenderWindow_isOpen(window))
    {
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        UpdatePlayer(player, (int [2]){(sfKeyboard_isKeyPressed(sfKeyLeft) - sfKeyboard_isKeyPressed(sfKeyRight)),
                                       (sfKeyboard_isKeyPressed(sfKeyUp) - sfKeyboard_isKeyPressed(sfKeyDown))},
                     (sfKeyboard_isKeyPressed(sfKeyD) - sfKeyboard_isKeyPressed(sfKeyQ)) * 11e-2);

        //clear_buffer(fbuffer);

        //printf("%i", *sfMouse_getPosition(window)[0]);

        //display_map(map, fbuffer);
        //display_player(player, fbuffer);

        //draw_rect(fbuffer, 0, 0, fbuffer->width, fbuffer->height/2, (char[4]){0, 255, 255, 255});
        //draw_rect(fbuffer, 0, fbuffer->height/2, fbuffer->width, fbuffer->height, (char[4]){22, 64, 22, 255});

        //sfTexture_updateFromPixels(texture, fbuffer->pixels, screen_size[0], screen_size[1], 0, 0);

        sfSprite_setTexture(sprite, texture, sfFalse);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        RenderRays(window, player, map, screen_size);

        /*for (int i = 0; i < width; i++) {
            sfSprite_setPosition(sprites[i], (sfVector2f){i, i});
            sfRenderWindow_drawSprite(window, sprites[i], 0);
        }*/
        sfRenderWindow_display(window);
    }

    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);

    free(player);

    for (int i = 0; i < map->texture->width; i++) {
        free(map->texture->cuts[i]);
    }
    free(map->texture);
    free(map);

    return 0;
}
