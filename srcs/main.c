/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:02:21 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/27 13:27:46 by pmaryjo          ###   ########.fr       */
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

static void	test_print_str_arr(char **arr)
{
	if (!arr)
		return ;
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

static void	test_print_point(t_point *point)
{
	printf("{x = %f, y = %f}\n", point->x, point->y);
}

static void	test_print_vector(t_vector *vector)
{
	printf("[\n");
	printf("\tbegin: ");
	test_print_point(vector->begin);
	printf("\tend: ");
	test_print_point(vector->end);
	printf("]\n");
}

static void	test_print_square(t_square *square)
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

static void	test_print_map_line(t_map_line *map_line)
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

static void	test_print_map(t_map *map)
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

static void	test_vector(void)
{
	t_point		*begin_1 = geom_init_point(1, 1);
	t_point		*end_1 = geom_init_point(2, 2);

	t_point		*begin_2 = geom_init_point(-3, -3);
	t_point		*end_2 = geom_init_point(-6, -6);

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

static void	test_angle(void)
{
	t_point		*begin_1 = geom_init_point(0, 0);
	t_point		*end_1 = geom_init_point(0, 1);

	t_point		*begin_2 = geom_init_point(0, 0);
	t_point		*end_2 = geom_init_point(1, 1);

	t_vector	*vector_1 = geom_init_vector(begin_1, end_1);
	t_vector	*vector_2 = geom_init_vector(begin_2, end_2);

	printf("%f\n", geom_get_angle(vector_1, vector_2));

	geom_destroy_vector(vector_1);
	geom_destroy_vector(vector_2);
}

static void test_move_vector(void)
{
	double angle = 90;

	double x1 = 0, y1 = 1;

	double x2 = x1 * cos(angle * M_PI / 180.0) + y1 * sin(angle * M_PI / 180.0);
	double y2 = y1 * cos(angle * M_PI / 180.0) - x1 * sin(angle * M_PI / 180.0);

	printf("angle: %f\n", angle);
	printf("x=%f; y=%f\n", x2, y2);
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
	(void)test_print_str_arr;
	(void)test_print_point;
	(void)test_print_vector;
	(void)test_print_square;
	(void)test_print_map_line;
	(void)test_print_map;
	(void)test_vector;
	(void)test_angle;
	(void)test_move_vector;
	
	//test_vector();
	//test_angle();
	//test_move_vector();
	//return 0;
	
	run(argc, argv);
	return (0);
}