#include "header.h"

int	get_width(const char *canv)
{
	int i = -1;
	int	cur_len = 0;
	int max_len = 0;

	while (canv[++i])
	{
		if (canv[i] == '\n')
		{
			max_len = MAX(max_len, cur_len + 1);
			cur_len = -1;
		}
		cur_len++;
	}
	max_len = MAX(max_len, cur_len + 1);
	return (max_len);
}

int get_height(const char *canv)
{
	int i = -1;
	int height = 0;
	while (canv[++i])
		if (canv[i] == '\n')
			height++;
	return (height);
}

char	*get_rect(char *canv, int width, int height, char interior)
{
	int	i = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			canv[i++] = x == 0 || x == width - 1 ? '|' : y == 0 || y == height - 1 ? '-' : interior;
		canv[i++] = '\n';
	}
	canv[i] = '\0';
	return (canv);
}
