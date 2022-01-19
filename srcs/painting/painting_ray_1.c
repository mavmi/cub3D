/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:21:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/19 21:05:55 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

//static void	test_print_point(t_point *point)
//{
//	printf("{x = %d, y = %d, z = %d}\n", point->x, point->y, point->z);
//}

//static void	test_print_vector(t_vector *vector)
//{
//	printf("[\n");
//	printf("\tbegin: ");
//	test_print_point(vector->begin);
//	printf("\tend: ");
//	test_print_point(vector->end);
//	printf("]\n");
//}

static t_vector	*paint_get_ray_vector(t_painting *painting, t_ray *ray)
{
	int			delta;
	double		corner_angle;
	t_point		*begin;
	t_point		*end;
	t_vector	*corner_vector;
	t_vector	*ray_vector;

	if (!painting || !ray)
		return (NULL);
	begin = geom_init_point(painting->map->player->pos->x * PIXEL_SIZE,
				painting->map->player->pos->y * PIXEL_SIZE, 0);
	end = geom_init_point(painting->map->player->pos->x * PIXEL_SIZE,
				painting->map->player->pos->y * PIXEL_SIZE, 0);
	if (!begin || !end)
	{
		geom_destroy_point(begin);
		geom_destroy_point(end);
		return (NULL);
	}
	while (1)
	{
		corner_vector = paint_get_corner_vector(end, ray->quarter);
		if (!corner_vector)
		{
			geom_destroy_point(begin);
			geom_destroy_point(end);
			return (NULL);
		}
		corner_angle = geom_get_angle(ray->orient_vert, corner_vector);
		if (corner_angle > 90.0)
			corner_angle -= 90.0;
		if (ray->quarter_angle <= corner_angle)
			delta = (int)sqrt(pow(corner_vector->begin->y - corner_vector->end->y, 2))
					* tan(ray->quarter_angle * M_PI / 180.0);
		else
			delta = (int)sqrt(pow(corner_vector->begin->x - corner_vector->end->x, 2))
					* tan((90 - ray->quarter_angle) * M_PI / 180.0);
		
		//printf("start point: ");
		//test_print_point(end);
		//printf("corner: ");
		//test_print_vector(corner_vector);
		//printf("\t==============\n");
		
		if (ray->quarter == 1 && ray->quarter_angle <= corner_angle)
		{
			end->x += delta;
			end->y = end->y - end->y % PIXEL_SIZE;
		}
		else if (ray->quarter == 1 && ray->quarter_angle > corner_angle)
		{
			end->x = end->x - end->x % PIXEL_SIZE + PIXEL_SIZE;
			end->y -= delta;
		}
		else if (ray->quarter == 2 && ray->quarter_angle <= corner_angle)
		{
			end->x += delta;
			end->y = end->y - end->y % PIXEL_SIZE + PIXEL_SIZE;
		}
		else if (ray->quarter == 2 && ray->quarter_angle > corner_angle)
		{
			end->x = end->x - end->x % PIXEL_SIZE + PIXEL_SIZE;
			end->y += delta;
		}
		else if (ray->quarter == 3 && ray->quarter_angle <= corner_angle)
		{
			end->x -= delta;
			end->y = end->y - end->y % PIXEL_SIZE + PIXEL_SIZE;
		}
		else if (ray->quarter == 3 && ray->quarter_angle > corner_angle)
		{
			end->x = end->x - end->x % PIXEL_SIZE;
			end->y += delta;
		}
		else if (ray->quarter == 4 && ray->quarter_angle <= corner_angle)
		{
			end->x -= delta;
			end->y = end->y - end->y % PIXEL_SIZE;
		}
		else if (ray->quarter == 4 && ray->quarter_angle > corner_angle)
		{
			end->x = end->x - end->x % PIXEL_SIZE;
			end->y -= delta;
		}
		geom_destroy_vector(corner_vector);
			
//printf("begin: ");
//test_print_point(begin);
//printf("end: ");
//test_print_point(end);
//printf("\n");

		if (
			painting->map->lines[(end->y - end->y % PIXEL_SIZE)/PIXEL_SIZE]->line[(end->x - end->x % PIXEL_SIZE)/PIXEL_SIZE]->type == WALL
		)
		{
			break ;
		}
//test_print_vector(ray_vector);
//ray_vector = geom_init_vector(begin, end);
//paint_draw_vector(painting, ray_vector, COLOR_PLAYER);
	}
	ray_vector = geom_init_vector(begin, end);
	paint_draw_vector(painting, ray_vector, COLOR_PLAYER);
	printf("\n==--==--==--==--==--==--==--==--\n\n");
	if (ray_vector)
		return (ray_vector);
	geom_destroy_point(begin);
	geom_destroy_point(end);
	return (NULL);
}

void	paint_print_ray(t_painting *painting)
{
	t_ray		*ray;
	t_vector	*ray_vector;

	if (!painting)
		return ;
	ray = paint_get_ray_info(painting);
	if (!ray)
		return ;
	ray_vector = paint_get_ray_vector(painting, ray);
	if (!ray_vector)
	{
		paint_destroy_ray_info(ray);
		return ;	
	}
	//printf("aaa\n");
	//paint_draw_vector(painting, ray_vector);
	//printf("zzz\n");
	geom_destroy_vector(ray_vector);
	paint_destroy_ray_info(ray);
}
