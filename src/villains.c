#include "gameplay.h"
#include "utils.h"
#include <stdlib.h>

#define RAND_MAX 15

villain_t MoveEnnemy(villain_t ennemy)
{
	ennemyStep = randint();

	while (ennemy->alert_state == False)
	{
		ennemy.pos_x -= ennemyStep;
		//ennemy.pos_y -= ennemyStep;
		ennemy.pos_x += ennemyStep;
		//ennemy.pos_y += ennemyStep;
		//ennemy.pos_dir -= ennemyStep;
		//ennemy.pos_dir += ennemyStep;
	}
	return ennemy;
}

int attack_player(weapon)
{

}

/**
 * void DrawPlayer(SDL_Renderer * ren, PLAYER_STRUCT player)
{
    // Draw player
    COLOR_RED(ren);
    SDL_Point target = CreateTarget(player.x, player.y, player.dir, 20); // Calculate the end of the line used to indicate the players direction
    SDL_RenderDrawLine(ren, player.x, player.y, target.x, target.y);
}*/

