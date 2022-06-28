#include "utils.h"

PLAYER_STRUCT MovePlayer(PLAYER_STRUCT player)
{
    // Get a snapshot of the keyboard
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    // Check what keys where held down and if we are not at the edge of the screen
    if (keys[SDL_SCANCODE_W] && player.y > PLAYER_STEP_SIZE)
    {
        player.y -= PLAYER_STEP_SIZE;
    }

    if (keys[SDL_SCANCODE_A] && player.x > PLAYER_STEP_SIZE)
    {
        player.x -= PLAYER_STEP_SIZE;
    }

    if (keys[SDL_SCANCODE_S] && player.y < WINDOW_HEIGHT - PLAYER_STEP_SIZE)
    {
        player.y += PLAYER_STEP_SIZE;
    }

    if (keys[SDL_SCANCODE_D] && player.x < WINDOW_WIDTH /3 - PLAYER_STEP_SIZE)
    {
        player.x += PLAYER_STEP_SIZE;
    }
    
    if (keys[SDL_SCANCODE_Q])
    {
        player.dir -= PLAYER_STEP_SIZE;
    }

    if (keys[SDL_SCANCODE_E])
    {
        player.dir += PLAYER_STEP_SIZE;
    }

    return player;
}

SDL_Point CreateTarget(int x, int y, int dir, int dist)
{
    // Create point dist pixels away in dir direction from x and y
    SDL_Point target;

    double traslated = dir * (M_PI / 180.0); // Convert to radians
    target.x = round(x + dist * cos(traslated));
    target.y = round(y + dist * sin(traslated));

    return target;
}

int PointOnLine(int x1, int y1, int x2, int y2, int tx, int ty)
{
    // Check if a point is on a line segment
    if (fmin(x1, x2) <= tx && tx <= fmax(x1, x2) && fmin(y1, y2) <= ty  && ty <= fmax(y1, y2))
    {
        return TRUE;
    }

    return FALSE;
}

int PointDistance(int x1, int y1, int x2, int y2)
{
    // Find the distance between two points
    int out = sqrt( pow(x2 - x1, 2) + pow(y2 - y1, 2) );
    return out;
}

void DrawRays(SDL_Renderer * ren, PLAYER_STRUCT player, SDL_Point walls[MAX_WALL_COUNT][2], int wallCount)
{
    // Find ray and wall intersections and draw them
    SDL_Point target;
    SDL_Point closest;
    SDL_Rect rect;

    // The thickness the bars can be based on the window width
    int rayPrevieuwRenderStep = WINDOW_WIDTH * 0.6667 / PLAYER_FOV;
    int rayCount = 0;
    int closestDistance;
    rect.w = rayPrevieuwRenderStep; // We can pre calculate the width as this is a constant

    // Loop for each ray in fov at 1 degree step
    for (int a = player.dir - PLAYER_FOV /2; a < player.dir + PLAYER_FOV /2; a++)
    {
        rayCount++;
        target = CreateTarget(player.x, player.y, a, PLAYER_VIEW_RANGE); // Find the point at wich the ray is out of view distance
        closest = target;
        closestDistance = PLAYER_VIEW_RANGE;

        // Loop over each wall
        for (int i = 0; i < wallCount; i++)
        {
            // I wont go into detail of the actual math, it will be linked at the top
            float a1 = target.y - player.y;
            float b1 = player.x - target.x;
            float c1 = a1 * player.x + b1 * player.y;

            float a2 = walls[i][1].y - walls[i][0].y;
            float b2 = walls[i][0].x - walls[i][1].x;
            float c2 = a2 * walls[i][0].x + b2 * walls[i][0].y;

            float det = a1 * b2 - a2 * b1;

            // If its not parallel
            if (det != 0)
            {
                int x = (b2 * c1 - b1 * c2) / det;
                int y = (a1 * c2 - a2 * c1) / det;

                // If the point falls inside the wall and the ray
                if (PointOnLine(player.x, player.y, target.x, target.y, x, y) && 
                    PointOnLine(walls[i][0].x, walls[i][0].y, walls[i][1].x, walls[i][1].y, x, y))
                {
                    // Calculate the distance to the point
                    int dist = PointDistance(player.x, player.y, x, y);

                    // If its the closest wall, store it
                    if (dist < closestDistance)
                    {
                        closest.x = x;
                        closest.y = y;
                        closestDistance = dist;
                    }
                }
            }
        }

        // If the ray hit something
        if (closestDistance != PLAYER_VIEW_RANGE)
        {
            //COLOR_GREEN(ren);
            //SDL_RenderDrawLine(ren, player.x, player.y, closest.x, closest.y);

            // Draw the 3D preview
            rect.x = rayPrevieuwRenderStep * rayCount + WINDOW_WIDTH /3;
            rect.y = closestDistance /2;
            rect.h = WINDOW_HEIGHT - rect.y * 2;

            int brightness = 255 - closestDistance /2;

            SDL_SetRenderDrawColor(ren, brightness, brightness, brightness, 255);
            SDL_RenderFillRect(ren, &rect);
        }
    }
}

void DrawWalls(SDL_Renderer * ren, SDL_Point walls[MAX_WALL_COUNT][2], int wallCount)
{
    // Loop over each wall and draw it
    COLOR_WHITE(ren);

    for (int i = 0; i < wallCount; i++)
    {
        SDL_RenderDrawLine(ren, walls[i][0].x, walls[i][0].y, walls[i][1].x, walls[i][1].y);
    }
}

void DrawPlayer(SDL_Renderer * ren, PLAYER_STRUCT player)
{
    // Draw player
    COLOR_RED(ren);
    SDL_Point target = CreateTarget(player.x, player.y, player.dir, 20); // Calculate the end of the line used to indicate the players direction
    SDL_RenderDrawLine(ren, player.x, player.y, target.x, target.y);
}

void SendFrame(SDL_Renderer * ren)
{
    // Push the frame stored in the renderer to the screen
    COLOR_BLACK(ren);
    SDL_RenderPresent(ren);
    SDL_RenderClear(ren);
}
