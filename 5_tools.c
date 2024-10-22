#include "header.h"

void set_nonblocking_mode(int enable) {
  static struct termios oldt, newt;
  if (enable) {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  } else {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, 0);
  }
}

int print_entity(ENTITY elem, char *dst)
{
    return (print_string(elem.frame, dst, elem.position[0] - scroll[0], elem.position[1] - scroll[1]));
}

char *get_cropped_str(const char *ref, int height, int below_x, int after_x)
{
	int max_len = (after_x - below_x) * height + height;
    int ref_len = strlen(ref);
    char *new_str = malloc(max_len + 1);
    if (!new_str)
        return NULL;
    int index = 0;
    int i = 0;
    for (int y = 0; y < height; y++)
    {
        int has_reached = 0;
        index += below_x;
		if (index >= ref_len)
			break;
        for (int x = below_x; x < after_x; x++)
        {
            if (ref[index] == '\n') 
            {
                has_reached = 1;
                break;
            }
            if (ref[index] == '\0')
            {
                break;
            }
            new_str[i++] = ref[index++];
        }
        new_str[i++] = '\n';
        if (!has_reached)
        {
            while (ref[index] && ref[index] != '\n') 
                index++;
        }
        if (!ref[index])
            break;
        index++;
		if (index >= ref_len)
   			break;
    }
    new_str[i] = '\0';
    return new_str;
}

int print_string(char *src, char *dst, int x_start, int y_start)
{
	if (!src || !dst)
		return (0);
	int	dst_len = (int)strlen(dst);
	int src_height = get_height(src);
    int src_width = get_width(src);
    int dst_width = get_width(dst);
    int dst_height = get_height(dst);
    int i = 0, j = 0;
    int start_pos = dst_width * y_start + x_start;

    if (start_pos + (dst_width * src_height) < 0 || start_pos >= dst_len)
        return 0;
    if (y_start >= dst_height || x_start >= dst_width || x_start + src_width <= 0 || y_start + src_height < 0)
        return 0;
	
	while (y_start < 0 && src[i])
    {
        while (src[i] && src[i] != '\n')
            i++;
        if (src[i])
            i++;
        y_start++;
        start_pos += dst_width;
        if (start_pos >= dst_len)
            return 0;
    }

	char *dummy = NULL;
   	if (x_start < 0 || dst_width - x_start < src_width)
	{
		int below_x = x_start < 0 ? -x_start : 0;
		if (start_pos + j + below_x >= dst_len) return (0);
		int after_x = (dst_width - x_start > 0) ? dst_width - x_start - 1 : 0;
		dummy = get_cropped_str(src, get_height(src), below_x, after_x);
		dst_width = get_width(dst);
		start_pos += below_x;
	}
    else dummy = strdup(src);
    if (!dummy)
        return 0;
    while (dummy[i] && start_pos + j < dst_len)
    {
        if (dummy[i] == '\n')
        {
            start_pos += dst_width;
			if (start_pos + j >= dst_len) break;
            j = 0;
        }
        else
        {
            if (j < dst_width - x_start && start_pos + j < dst_len)
            {
				if (dummy[i] != ' ' && dst[start_pos + j] != PROJ_IC) dst[start_pos + j] = dummy[i];
                j++;
            }
        }
        i++;
    }

    free(dummy);
    return 1;
}

void flip_lines(char *str)
{
    int i = 0;
    while (str[i])
    {
        int line_start = i;
        int line_len = 0;
        while (str[i + line_len] && str[i + line_len] != '\n') 
            line_len++;
        int line_end = i + line_len - 1;
        while (line_start < line_end)
        {
            char tmp = str[line_start];
            str[line_start] = str[line_end--];
            str[line_end++] = tmp;
        }
        i += line_len;
        if (str[i] == '\n')
            i++;
    }
}


void print_colored_text(char *c, char cc, char *color)
{
  if (color != NULL)
  {
    if (c != NULL)
    {
      int i = 0;
      while (c[i])
        printf("%s%c\033[0m", color, c[i++]);
    }
    if (cc != '\0')
      printf("%s%c\033[0m", color, cc);
  }
  else
  {
    // Print without color
    if (c != NULL)
      printf("%s", c);
    if (cc != '\0')
      printf("%c", cc);
  }
}


int rand_range(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}