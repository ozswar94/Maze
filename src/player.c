#include "gameplay.h"
#include <stdlib.h>

#define RAND_MAX 50

/**
 *
 */

weapon_t weapGenerator()
{
	weapon_t weapon;
	weapon->weapPos = MovePlayer(player);
	weapon->shootRange = ;
	weapon->posRange = ;
	weapon->attack = rand();

	return weapon;
}

int shoot(weapon_t weapon)
{
	villain_t villain;
	SDL_Point target;
	SDL_Point closest;
	SDL_Point ennemy = villain;
	SDL_Rect rect;

	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	target = CreateTarget(weapon.weapPos_x, weapon.weapPos_y, weapon.weapPos_dir, PLAYER_VIEW_RANGE);
	closest = target;
	closestDistance = PLAYER_VIEW_RANGE;
	if (closestDistance != PLAYER_VIEW_RANGE)

			if (closest == ennemy)
			{
				if (keys[SDL_SCANCODE_F])
					ennemy->hp -= weapon->attack;
			}
		}
	}
	return ennemy->hp;

}

void DrawBullets(SDL_Renderer * ren, weapon_t weapon)
{
	COLOR_ORANGE(ren);

}
