#include "raycaster.h"

int init(t_sdl *sdl, t_raycaster *rc)
{
  sdl->window = NULL;
  sdl->renderer = NULL;
  rc->player_pos_x = INIT_P_POS_X;
  rc->player_pos_y = INIT_P_POS_Y;
  rc->player_dir_x = INIT_P_DIR_X;
  rc->player_dir_y = INIT_P_DIR_Y;
  rc->player_plane_x = INIT_P_PLANE_X;
  rc->player_plane_y = INIT_P_PLANE_Y;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    fprintf(stderr,"SDL initialization failed (%s)\n", SDL_GetError());
    return (-1);
  }
  if (SDL_CreateWindowAndRenderer(WIN_X, WIN_Y, 0, &sdl->window, &sdl->renderer) != 0)
  {
    fprintf(stderr,"Window creation failed (%s)\n", SDL_GetError());
    return (-1);
  }
  return (0);
}


void render_frame(t_sdl *sdl)
{
  SDL_RenderPresent(sdl->renderer);
  SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(sdl->renderer);
}


int handle_events(t_raycaster *rc)
{
  SDL_Event event;
  double oldDirX;
  double oldPlaneX;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
      return (-1);
    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_UP)
      {
        if(worldMap[(int)(rc->player_pos_x + rc->player_dir_x * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
          rc->player_pos_x += rc->player_dir_x * MV_SPEED;
        if(worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y + rc->player_dir_y * MV_SPEED)] == 0)
          rc->player_pos_y += rc->player_dir_y * MV_SPEED;
      }
      if (event.key.keysym.sym == SDLK_DOWN)
      {
        if(worldMap[(int)(rc->player_pos_x - rc->player_dir_x * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
          rc->player_pos_x -= rc->player_dir_x * MV_SPEED;
        if(worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y - rc->player_dir_y * MV_SPEED)] == 0)
          rc->player_pos_y -= rc->player_dir_y * MV_SPEED;
      }
      if (event.key.keysym.sym == SDLK_RIGHT)
      {
        oldDirX = rc->player_dir_x;
        rc->player_dir_x = rc->player_dir_x * cos(-ROT_SPEED) - rc->player_dir_y * sin(-ROT_SPEED);
        rc->player_dir_y = oldDirX * sin(-ROT_SPEED) + rc->player_dir_y * cos(-ROT_SPEED);
        oldPlaneX = rc->player_plane_x;
        rc->player_plane_x = rc->player_plane_x * cos(-ROT_SPEED) - rc->player_plane_y * sin(-ROT_SPEED);
        rc->player_plane_y = oldPlaneX * sin(-ROT_SPEED) + rc->player_plane_y * cos(-ROT_SPEED);
      }
      if (event.key.keysym.sym == SDLK_LEFT)
      {
        oldDirX = rc->player_dir_x;
        rc->player_dir_x = rc->player_dir_x * cos(ROT_SPEED) - rc->player_dir_y * sin(ROT_SPEED);
        rc->player_dir_y = oldDirX * sin(ROT_SPEED) + rc->player_dir_y * cos(ROT_SPEED);
        oldPlaneX = rc->player_plane_x;
        rc->player_plane_x = rc->player_plane_x * cos(ROT_SPEED) - rc->player_plane_y * sin(ROT_SPEED);
        rc->player_plane_y = oldPlaneX * sin(ROT_SPEED) + rc->player_plane_y * cos(ROT_SPEED);
      }
    }
  }
  return (0);
}
