//mood_2.h

#define ABS(value) (((value) >= 0) ? (value) : (-1*(value)))

#ifndef HEADERDIG
    #define HEADERDIG

typedef struct FrameBufferStruct {
    unsigned char *pixels;
    int width;
    int heigth;
    int size[2];
} FrameBuffer;

typedef struct PlayerStruct {
    int pos[2];
    char color[4];
    long double angle;
} Player;

char *read_file(char *filename);
void draw_rect(FrameBuffer *fbuffer, int xpos, int ypos,
                 int width, int heigth, char color[4]);
void draw_circle(FrameBuffer *fbuffer, int xpos, int ypos,
                 int radius, char color[4]);
void draw_line(FrameBuffer *fbuffer, int p0[2], int p1[2], char color[4]);
void display_player(Player *player, FrameBuffer *fbuffer);
Player *new_player(int x, int y, char color[4]);

#endif
