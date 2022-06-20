#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define HEIGHT_SCREEN	480
#define WIDTH_SCREEN	640

int main(void)
{
	/* 5 x 6; 1 = mur et 0 = vide */
	int map [5][6] = {
		{1, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0},
		{0, 1, 0, 0, 0, 0},
		{0, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1}
	};
	SDL_Window *window = NULL;
	SDL_Renderer *ren = NULL;
	SDL_Rect rect = {100, 100, 10, 10};
	SDL_Event event;
	int status = EXIT_FAILURE;
	int status_event = 1;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		fprintf(stderr, "ERROR SDL_Init: %s\n", SDL_GetError());
		goto Quit;
	}

	window = SDL_CreateWindow("rectangle mouve", SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											WIDTH_SCREEN, HEIGHT_SCREEN, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "ERROR SDL_CreateWindow: %s\n", SDL_GetError());
		goto Quit;
	}

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!ren)
	{
		fprintf(stderr, "ERROR SDL_CreateWindow: %s\n", SDL_GetError());
		goto Quit;
	}

	while (status_event)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				status_event = 0;
				break;	
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_w:
						if (rect.y > 0)
							rect.y -= 5;
					break;
					case SDLK_s:
						if (rect.y < HEIGHT_SCREEN - 10)
						rect.y += 5;
					break;
					case SDLK_a:
						if (rect.x > 0)
							rect.x -= 5;
					break;
					case SDLK_d:
						if (rect.x < WIDTH_SCREEN - 10)
						rect.x += 5;
					break;
				}
			}
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			SDL_RenderClear(ren);
			SDL_RenderDrawRect(ren, &rect);
			SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
			SDL_RenderFillRect(ren, &rect);
			SDL_RenderPresent(ren);
		}

	}

	status = EXIT_SUCCESS;
Quit:
	if (ren)
		SDL_DestroyRenderer(ren);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	return status;
}