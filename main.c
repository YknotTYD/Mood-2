//main.c

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Window/Keyboard.h>
//#include <SFML/System/Time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "mood_2.h"

//draw fbuff
//put fbuff in text
//link text to sprite
//draw sprite on window
//flip

FrameBuffer *new_frame_buffer(int width, int heigth)
{
    FrameBuffer *fbuffer = malloc(sizeof(FrameBuffer));

    fbuffer->pixels = malloc(32*width*heigth);
    fbuffer->width = width;
    fbuffer->heigth = heigth;

    fbuffer->size[0] = width;
    fbuffer->size[1] = heigth;

    return fbuffer;
}

void clear_buffer(FrameBuffer *fbuffer)
{
    memset((fbuffer->pixels), 55, (fbuffer->width*fbuffer->heigth*32));
}

int main()
{
    const int screen_size[2]={1500, 700};

    Player *player = new_player(222, 222, (char[4]){255, 0, 0, 255});

    srand(time(NULL));

    sfVideoMode mode = {screen_size[0], screen_size[1], 32};
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite; 
    FrameBuffer *fbuffer;
    sfEvent event;

    window = sfRenderWindow_create(mode, "Mood 2", sfResize | sfClose, NULL);
    fbuffer = new_frame_buffer(screen_size[0], screen_size[1]);
    texture = sfTexture_create(screen_size[0], screen_size[1]);
    sprite = sfSprite_create();

    while (sfRenderWindow_isOpen(window))
    {
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        //player->pos[0]++;
        player->angle += 1e-2;

        clear_buffer(fbuffer);

        display_player(player, fbuffer);

        sfTexture_updateFromPixels(texture, fbuffer->pixels, screen_size[0], screen_size[1], 0, 0);                         
        sfSprite_setTexture(sprite, texture, sfFalse);
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfRenderWindow_display(window);
    }

    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);

    free(player);

    return 0;
}
