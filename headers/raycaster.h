#ifndef RAYCASTER_H
#define RAYCASTER_H

/* System includes */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

/* Map */
#define mapWidth 24
#define mapHeight 24
extern int worldMap[mapWidth][mapHeight];

/* Initial values */
#define WIN_X           800
#define WIN_Y           600
#define INIT_P_POS_X    22
#define INIT_P_POS_Y    12
#define INIT_P_DIR_X    -1
#define INIT_P_DIR_Y    0
#define INIT_P_PLANE_X  0
#define INIT_P_PLANE_Y  0.66
#define MV_SPEED        0.199
#define ROT_SPEED       0.1745
#define AMB_LIGHT       7

/* Colors */
#define WHITE           0xFFFFFF
#define RED             0xFF0000
#define GREEN           0x00FF00
#define BLUE            0x0000FF
#define BLACK           0x000000

/* Structures */
typedef struct s_sdl
{
  SDL_Window      *window;
  SDL_Renderer    *renderer;
  SDL_Surface     *image;
  SDL_Texture     *texture;
} t_sdl;


typedef struct s_raycaster
{
  double          player_pos_x;
  double          player_pos_y;
  double          player_dir_x;
  double          player_dir_y;
  double          player_plane_x;
  double          player_plane_y;
  double          ray_dir_x;
  double          ray_dir_y;
  int             map_x;
  int             map_y;
  double          side_dist_x;
  double          side_dist_y;
  double          delta_dist_x;
  double          delta_dist_y;
  int             step_x;
  int             step_y;
  int             side;
  int             draw_start;
  int             draw_end;
  double          perp_wall_dist;
} t_raycaster;

/* Prototype */
SDL_Color convert_color(int hexa_value);
SDL_Color select_wall_color(int map_x, int map_y);
SDL_Color apply_night_effect(SDL_Color color, double distance);
int init(t_sdl *sdl, t_raycaster *rc);
void initial_calc(t_raycaster *rc, int x);
void perform_dda(t_raycaster *rc);
void calc_wall_height(t_raycaster *rc);
void raw_vert_line(t_sdl *sdl, t_raycaster *rc, int x);
void render_frame(t_sdl *sdl);
int handle_events(t_raycaster *rc);
void raycaster(t_sdl *sdl, t_raycaster *rc);

#endif /* !RAYCASTER_H */
