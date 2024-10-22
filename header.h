#ifndef HEADER_H
# define HEADER_H

#include "ascii.h"
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

// COLORS
#define RED "\033[31m"
#define BRIGHT_RED "\033[91m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define LIGHT_BLUE "\033[38;5;117m"
#define DIM_WHITE "\033[38;5;250m"
#define PALE_YELLOW "\033[38;5;229m"
#define SOFT_BLUE "\033[38;5;153m"

#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define ORANGE "\033[38;5;214m"
#define BROWN "\033[38;5;94m"
#define DARK_GREEN "\033[38;5;22m"

#define REFRES_SPEED 50000
#define SCRN_WIDTH 150
#define SCRN_HEIGHT (SCRN_WIDTH / 2)
#define SCREEN_SIZE (SCRN_WIDTH + (SCRN_HEIGHT * SCRN_WIDTH + 1))
#define MAX_CONTENT SCRN_WIDTH * SCRN_HEIGHT
#define GRASS_AMNT 50
#define TREES_MAX 20
#define CLOUDS_MAX 2
#define SCROLL_LIMIT 50
#define MOVE_AMOUNT 100000
#define JMP_AMOUNT 4

#define MOBS_AMOUNT 200
#define SPIDER_AMOUNT 200

#define PROJ_AMOUNT 100

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a < b ? a : b))
#define MINMAX(a, b, c) ()

#define GAME_KEYS 

typedef enum ACTION {idle, move, attack, jump, falling, death} ACTION;
typedef enum DIRECTION {down, left, right, up} DIRECTION;

#define GRN_GRASS '}'
#define ORNG_GRASS '{'
#define RED_GRASSS '&'

#define PROJ_IC 'K'
#define LEAF_IC 'L'

#define GRAB_K 'g'
#define DROP_K 'd'
#define SHOOT_K ' '
#define CHNG_WEAP 'f'

#define RIFLE_PUSH 4
#define WEAP_AMNT 3
typedef struct s_WEAPON
{
	int x_pos, y_pos, pow, reload, speed, mun, start_mun, active;
	char gfx[4][2][500];
	char color[20];
	char label[20];
} WEAPON;

typedef struct BULLET
{
	int speed;
	char *color;
} BULLET;


typedef struct s_ENTITY
{
	DIRECTION 	dir;
	ACTION 		action;
	WEAPON 		weap;
	int		position[2], movement[2], prev_movement[2];
	int		width, height, jumps, hp, maxHP, speed, hurt;
	char	frame[MAX_CONTENT];
	char	idle[4][MAX_CONTENT];
	char	move[4][2][MAX_CONTENT];
	char	attack[4][MAX_CONTENT];
	char	jump[4][MAX_CONTENT];
	char	falling[4][MAX_CONTENT];
	char	sleep[4][MAX_CONTENT];
	char	death[4][MAX_CONTENT];
}	ENTITY;


#define BOSS_AMNT 10
extern ENTITY PLAYER;
extern ENTITY MOBS[MOBS_AMOUNT];
extern ENTITY BOSS[BOSS_AMNT];
extern ENTITY SPIDERS[SPIDER_AMOUNT];
extern WEAPON WEAPONS[3];

extern int 	game_time;
extern char screen[];
extern char prvscrn[];
extern int	projectiles[100][4];
extern int	WEAPON_INDEX;
extern int	PROJ_FIRED;
extern int 	INV_FRAME;

extern int	input;
extern int	prev_input;
extern int	movement[2];
extern int	scroll[2];
extern int	grass[GRASS_AMNT][2];
extern int	trees[TREES_MAX][2];
extern int	clouds[CLOUDS_MAX][2];

char	*get_rect(char canv[], int width, int height, char interior);
int 	get_height(const char *canv);
int		get_width(const char *canv);
void 	set_nonblocking_mode(int enable);
int		print_entity(ENTITY elem, char *dst);
void	init_game();
int 	update_game();
int 	render_game();
int 	rand_range(int min, int max);
int		print_string(char *src, char *dst, int x_start, int y_start);
char	*get_cropped_str(const char *ref, int height, int below_x, int after_x);
int 	check_crop();
void	render_env();
void 	print_colored_text(char *c, char cc, char *color);
int 	is_in_canv(int x, int y, char *src, char *dst);

#endif