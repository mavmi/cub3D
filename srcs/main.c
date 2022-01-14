#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/painting.h"
#include "../include/parser.h"
#include "../include/utils.h"

void	test_print_str_arr(char **arr)
{
	if (!arr)
		return ;
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

void	test_print_point(t_point *point)
{
	printf("x = %f\ny = %f\n", point->x, point->y);
}

void	test_print_square(t_square *square)
{
	if (!square)
	{
		printf("square is NULL\n");
		return ;
	}
	printf("top left x = %ld\n", square->top_left_x);
	printf("top left y = %ld\n", square->top_left_y);
	printf("type = %c\n", square->type);
}

void	test_print_map_line(t_map_line *map_line)
{
	size_t	x;

	if (!map_line)
	{
		printf("map_line is NULL\n");
		return ;
	}
	x = 0;
	while (x < map_line->width)
	{
		test_print_square(map_line->line[x]);
		printf("\n");
		x++;
	}
}

void	test_print_map(t_map *map)
{
	size_t	y;

	if (!map)
	{
		printf("map_line is NULL\n");
		return ;
	}
	y = 0;
	while (y < map->height)
	{
		test_print_map_line(map->lines[y]);
		printf("\n\t======================\n\n");
		y++;
	}
}

// ************************************************** //

int main(int argc, char **argv){
	t_map	*map;
	
	if (argc != 2){
		printf("Bad input\n");
		exit(1);
	}
	map = pars_get_map(argv[1]);
	if (!map)
	{
		printf("Parser error\n");
		exit(1);
	}
	paint_init(map);
	return (0);
}
