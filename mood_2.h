//mood_2.h

#define ABS(value) (((value) >= 0) ? (value) : (-1*(value)))

#ifndef HEADERDIG
    #define HEADERDIG

typedef struct FrameBuffer {
    unsigned char *pixels;
    int width;
    int height;
    int size[2];
} FrameBuffer;

typedef struct Player {
    long double pos[2];
    char color[4];
    long double angle;
    long double FOV;
    int ray_count;
    long double ray_step;
    long double speed;
} Player;

typedef struct Map {
    int line_count;
    int **lines;
} Map;

char *read_file(char *filename);
void draw_rect(FrameBuffer *fbuffer, int xpos, int ypos,
                 int width, int heigth, char color[4]);
void draw_circle(FrameBuffer *fbuffer, int xpos, int ypos,
                 int radius, char color[4]);
void draw_line(FrameBuffer *fbuffer, int p0[2], int p1[2], char color[4]);
void display_player(Player *player, FrameBuffer *fbuffer);
Player *new_player(long double x, long double y, long double speed, int FOV, int ray_count);
void UpdatePlayer(Player *player, int movect[2], long double angle_offset);
Map *new_map();
void display_map(Map *map, FrameBuffer *fbuffer);
void RenderRays(FrameBuffer *fbuffer, Player *player, Map *map);
long double square(long double n);

#endif
