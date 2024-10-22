#include "header.h"

char 	screen[SCREEN_SIZE];
char 	prvscrn[SCREEN_SIZE];
ENTITY 	PLAYER;
ENTITY 	MOBS[MOBS_AMOUNT];
ENTITY 	BOSS[BOSS_AMNT];
ENTITY 	SPIDERS[SPIDER_AMOUNT];
ENTITY 	PLATFORMS[10];
WEAPON	WEAPONS[3];

int		grass[GRASS_AMNT][2];
int		trees[TREES_MAX][2];
int		clouds[CLOUDS_MAX][2];
int		projectiles[100][4];

int		input, prev_input;
int		movement[2];
int		scroll[2];
int		game_time;

int		WEAPON_INDEX = 0;
int		PROJ_FIRED = 0;
int 	INV_FRAME = 0;

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char roc[MAX_CONTENT];
	get_rect(roc, 20, 20, '#');

	scroll[0] = scroll[1] = movement[0] = movement[1] = 0;
	init_game();
	game_time = 0;
	while (1)
	{
		if (input == 'q') break;
		get_rect(screen, SCRN_WIDTH, SCRN_HEIGHT, ' ');
		update_game();
		print_string(roc, screen, 5 - scroll[0], SCRN_HEIGHT - 30 - scroll[1]);
		render_game();
		usleep(REFRES_SPEED);
		game_time ++;
	}

	return (0);
}
