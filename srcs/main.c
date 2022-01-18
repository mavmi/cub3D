/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:02:21 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/18 17:16:47 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/geometry.h"
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
	printf("{x = %d, y = %d, z = %d}\n", point->x, point->y, point->z);
}

void	test_print_vector(t_vector *vector)
{
	printf("[\n");
	printf("\tbegin: ");
	test_print_point(vector->begin);
	printf("\tend: ");
	test_print_point(vector->end);
	printf("]\n");
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

void	test_vector(void)
{
	t_point		*begin_1 = geom_init_point(1, 1, 0);
	t_point		*end_1 = geom_init_point(2, 2, 0);

	t_point		*begin_2 = geom_init_point(-3, -3, 0);
	t_point		*end_2 = geom_init_point(-6, -6, 0);

	t_vector	*vector_1 = geom_init_vector(begin_1, end_1);
	t_vector	*vector_2 = geom_init_vector(begin_2, end_2);
	t_vector	*vector_sum = geom_sum_vectors(vector_1, vector_2);
	
	test_print_vector(vector_1);
	test_print_vector(vector_2);
	test_print_vector(vector_sum);

	geom_destroy_vector(vector_1);
	geom_destroy_vector(vector_2);
	geom_destroy_vector(vector_sum);
}

void	test_angle(void)
{
	t_point		*begin_1 = geom_init_point(0, 0, 0);
	t_point		*end_1 = geom_init_point(0, 1, 0);

	t_point		*begin_2 = geom_init_point(0, 0, 0);
	t_point		*end_2 = geom_init_point(1, 1, 0);

	t_vector	*vector_1 = geom_init_vector(begin_1, end_1);
	t_vector	*vector_2 = geom_init_vector(begin_2, end_2);

	printf("%f\n", geom_get_angle(vector_1, vector_2));

	geom_destroy_vector(vector_1);
	geom_destroy_vector(vector_2);
}

// ************************************************** //

void	run(int argc, char **argv)
{
	t_map	*map;

	(void)argc;
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
}

int main(int argc, char **argv)
{
	(void)argc; (void)argv;
	
	//test_vector();
	//test_angle();
	run(argc, argv);
	return (0);
}
