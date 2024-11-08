//main.c

#include "mood_2.h"
#include <math.h>
#include <stdio.h>

long double square(long double n)
{
    return n * n;
}

void draw_rect(FrameBuffer *fbuffer, int xpos, int ypos,
                 int width, int heigth, char color[4])
{
    for (int y = ypos; y < heigth + ypos; y++){
        for (int x = xpos; x < width + xpos; x++){
        
            if (x < 0  || x >= (int)(fbuffer->width) ||
                y >= (int)(fbuffer->height) || y < 0) {
                continue;
            }

            for (int i = 0; i < 4; i++) {
                (fbuffer->pixels)[(x+y*(fbuffer->width))*4+i]=color[i];
            }
        }
    }
}

void draw_circle(FrameBuffer *fbuffer, int xpos, int ypos,
                 int radius, char color[4])
{
    xpos -= radius/2;
    ypos -= radius/2;
    
    for (int y = ypos; y < radius + ypos; y++){
        for (int x = xpos; x < radius + xpos; x++){
        
            if (x < 0  || x >= (int)(fbuffer->width) ||
                y >= (int)(fbuffer->height) || y < 0 ||
                square(x-(xpos + radius/2)) +
                square(y-(ypos + radius/2)) >= square(radius/2)){
                continue;
            }

            for (int i = 0; i < 4; i++) {
                (fbuffer->pixels)[(x+y*(fbuffer->width))*4+i]=color[i];
            }
        }
    }
}


void draw_line(FrameBuffer *fbuffer, int p0[2], int p1[2], char color[4])
{
    double x = p0[0];
    double y = p0[1];
    double norm = sqrt(square(p1[0]-p0[0]) + square(p1[1]-p0[1]));
    double vect[2] = {p1[0]-p0[0], p1[1]-p0[1]};

    vect[0] /= norm;
    vect[1] /= norm;

    for (int i = 0; i < norm + 1; i++) {

        if ((int)x >= 0 && (int)x < fbuffer->width &&
            (int)y >= 0 && (int)y < fbuffer->height) {
            for (int i = 0; i < 4; i++) {
                (fbuffer->pixels)[((int)x+(int)y*(fbuffer->width))*4+i]=color[i];
            }
        }
        x += vect[0];
        y += vect[1];
    }
}
