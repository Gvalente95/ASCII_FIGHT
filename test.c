#include "header.h"

int check_crop()
{
	char txt[MAX_CONTENT];
	get_rect(txt, 25, 25, 'l');

	for (int x = 0; x < 20; x++)
	{
		char *new = get_cropped_str(txt, get_height(txt), x, get_width(txt) - x);
		printf("\n\n%d %d\n %s\n\n", x, get_width(txt) - x, new);
		free(new);
	}
	return (1);
}