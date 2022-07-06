#include "gameplay.h"
#include "utils.h"
#include <stdlib.h>

#define RAND_MAX 15

/**
 * MoveEnnemy - setup a routine for a villain
 * @ennemy: ennemy to setup the routine to
 *
 * Return: the ennemy and its position
 */
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

/**
 * attack_player - function for the ennemies attacks
 *
 * Return: player health
 */
int attack_player()
{
	villain_t = enemy;
	if (/*villain see player*/)
	{
		enemy->alertState = True;
		while (enemy->alertState == True)

	}

}

/**
 * void DrawPlayer(SDL_Renderer * ren, PLAYER_STRUCT player)
{
    // Draw player
    COLOR_RED(ren);
    SDL_Point target = CreateTarget(player.x, player.y, player.dir, 20); // Calculate the end of the line used to indicate the players direction
    SDL_RenderDrawLine(ren, player.x, player.y, target.x, target.y);
}*/

