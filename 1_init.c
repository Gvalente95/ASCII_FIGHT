#include "header.h"

void init_entity(ENTITY *ent, int x_pos, int y_pos, int speed, int hp)
{
	ent->hp = ent->maxHP = hp;
	ent->hurt = 0;
	ent->speed = speed;
	ent->position[0] = x_pos;
	ent->position[1] = y_pos;
	ent->jumps = ent->hurt = 0;

	strncpy(ent->idle[0], plr_idle_down1, MAX_CONTENT);
	strncpy(ent->idle[1], plr_idle_left, MAX_CONTENT);
	strncpy(ent->idle[2], plr_idle_right, MAX_CONTENT);
	strncpy(ent->idle[3], plr_idle_up, MAX_CONTENT);

	strncpy(ent->move[0][0], plr_mv_down1, MAX_CONTENT);
	strncpy(ent->move[0][1], plr_mv_down2, MAX_CONTENT);
	strncpy(ent->move[1][0], plr_mv_left1, MAX_CONTENT);
	strncpy(ent->move[1][1], plr_mv_left2, MAX_CONTENT);
	strncpy(ent->move[2][0], plr_mv_right1, MAX_CONTENT);
	strncpy(ent->move[2][1], plr_mv_right2, MAX_CONTENT);
	strncpy(ent->move[3][0], plr_mv_up1, MAX_CONTENT);
	strncpy(ent->move[3][1], plr_mv_up2, MAX_CONTENT);

	strncpy(ent->jump[0], plr_mv_down1, MAX_CONTENT);
	strncpy(ent->jump[1], plr_mv_left1, MAX_CONTENT);
	strncpy(ent->jump[2], plr_mv_right1, MAX_CONTENT);
	strncpy(ent->jump[3], plr_mv_up1, MAX_CONTENT);

	strncpy(ent->falling[0], plr_idle_down1, MAX_CONTENT);
	strncpy(ent->falling[1], plr_idle_left, MAX_CONTENT);
	strncpy(ent->falling[2], plr_idle_right, MAX_CONTENT);
	strncpy(ent->falling[3], plr_idle_up, MAX_CONTENT);

	strncpy(ent->attack[0], plr_mv_down2, MAX_CONTENT);
	strncpy(ent->attack[1], plr_spell_left, MAX_CONTENT);
	strncpy(ent->attack[2], plr_spell_right, MAX_CONTENT);
	strncpy(ent->attack[3], plr_mv_up2, MAX_CONTENT);
	strncpy(ent->frame, plr_idle_down1, MAX_CONTENT);

	ent->width = get_width(plr_idle_down1);
	ent->height = get_height(plr_idle_down1);
}

void	init_env()
{
	int spread = 200;
	int min_spr = -spread;
	int max_hor_spread = SCRN_WIDTH + spread;
	int max_ver_spread = SCRN_HEIGHT + spread;
	for (int x = 0; x < GRASS_AMNT; x++)
	{
		grass[x][0] = rand_range(min_spr, max_hor_spread);
		grass[x][1] = rand_range(min_spr, max_ver_spread);
	}
	for (int x = 0; x < TREES_MAX; x++)
	{
		trees[x][0] = rand_range(min_spr, max_hor_spread);
		trees[x][1] = rand_range(min_spr, max_ver_spread);
	}
	for (int x = 0; x < CLOUDS_MAX; x++)
	{
		clouds[x][0] = rand_range(min_spr, max_hor_spread);
		clouds[x][1] = rand_range(min_spr, max_ver_spread);
	}
}

void	init_weapons()
{
	const char 	NAMES[3][50] = {"RIFLE", "SWORD", "BOMB"};
	int		RELOAD[3] = {3, 1, 5};
	int		POWER[3] = {5, 2, 10};
	int		START_MUN[3] = {20, 99, 15};
	const char 	RIFLE_IDLE[4][50] = {RIFLE_BTM_IDLE, RIFLE_L_ATK, RIFLE_R_ATK, RIFLE_TOP_IDLE};
	const char 	RIFLE_ATK[4][50] = {RIFLE_BTM_IDLE, RIFLE_L_IDLE, RIFLE_R_IDLE, RIFLE_TOP_IDLE};
	const char 	SWD_IDLE[4][50] = {SWD_BTM_IDLE, SWD_L_IDLE, SWD_R_IDLE, SWD_TOP_IDLE};
	const char 	SWD_ATK[4][50] = {SWD_BTM_IDLE, SWD_L_ATK, SWD_R_ATK, SWD_TOP_IDLE};
	for (int x = 0; x < WEAP_AMNT; x++)
	{
		strncpy(WEAPONS[x].label, NAMES[x], 20);
		WEAPONS[x].x_pos = WEAPONS[x].y_pos = 0;
		WEAPONS[x].start_mun = WEAPONS[x].mun = START_MUN[x];
		WEAPONS[x].pow = POWER[x];
		WEAPONS[x].active = 0;
		WEAPONS[x].pow = 0;
		WEAPONS[x].reload = RELOAD[x];
		for (int dir = 0; dir < 4; dir++)
		{
			strncpy(WEAPONS[x].gfx[dir][0], x == 0 ? RIFLE_IDLE[dir] : x == 1 ? SWD_IDLE[dir] : "O", 500);
			strncpy(WEAPONS[x].gfx[dir][1], x == 0 ? RIFLE_ATK[dir] : x == 1 ? SWD_ATK[dir] : "O", 500);
		}
	}
	PLAYER.weap.active = 1;
}

void	init_game()
{
	set_nonblocking_mode(1);
	srand(time(NULL));
	get_rect(screen, SCRN_WIDTH, SCRN_HEIGHT, ' ');
	init_env();
	init_weapons();

	init_entity(&PLAYER, SCRN_WIDTH/2, SCRN_HEIGHT/2, 4, 10);
	int distance = 500;
	for (int x = 0; x < MOBS_AMOUNT; x++)
		init_entity(&MOBS[x], (rand_range(50, distance) * ((rand() % 2 == 0) ? 1 : -1)), (rand_range(50, distance) * ((rand() % 2 == 0) ? 1 : -1)), 1, 3);

	int GFXAM = 2;
	char BOSSGFX[2][MAX_CONTENT] = {SHIELD_GFX_0, BOSS1};
	char BOSSGFX_1[2][MAX_CONTENT] = {SHIELD_GFX_1, BOSS1};

	for (int x = 0; x < BOSS_AMNT; x++)
	{
		init_entity(&BOSS[x], (rand_range(50, distance) * ((rand() % 2 == 0) ? 1 : -1)), (rand_range(50, distance) * ((rand() % 2 == 0) ? 1 : -1)), 1, 10);
		for (int dir = 0; dir < 4; dir++) 
		{
			char *GFX = BOSSGFX[x > GFXAM - 1? GFXAM - 1 : x];
			char *GFX_1 = BOSSGFX_1[x > GFXAM - 1? GFXAM - 1 : x];

			strncpy(BOSS[x].move[dir][0], GFX, MAX_CONTENT);
			strncpy(BOSS[x].move[dir][1],GFX_1, MAX_CONTENT);	
			strncpy(BOSS[x].idle[dir], GFX_1, MAX_CONTENT);
			BOSS[x].width = get_width(GFX);
			BOSS[x].height = get_height(GFX_1);
		}
	}
	for (int x = 0; x < SPIDER_AMOUNT; x++)
	{
		init_entity(&SPIDERS[x], (rand_range(50, distance) * ((rand() % 2 == 0) ? 1 : -1)), (rand_range(50, distance) * ((rand() % 2 == 0) ? 1 : -1)), 2, 1);
		SPIDERS[x].width = 3;
		SPIDERS[x].height = 3;
		for (int dir = 0; dir < 4; dir++) 
		{
			strncpy(SPIDERS[x].move[dir][0], SPIDER, MAX_CONTENT);
			strncpy(SPIDERS[x].move[dir][1], SPIDER_2, MAX_CONTENT);	
			strncpy(SPIDERS[x].idle[dir], SPIDER, MAX_CONTENT);
		}
	}
	memset(projectiles, 0, 100);
}