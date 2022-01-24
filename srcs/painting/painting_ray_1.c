/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:21:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/24 22:10:19 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

static void	paint_append_vector_4(t_vector *ray_vector, t_ray *ray_info,
					double corner_angle, int delta)
{
	if (ray_info->quarter_angle <= corner_angle)
	{
		ray_vector->end->x -= delta;
		if (ray_vector->end->y % PIXEL_SIZE)
			ray_vector->end->y = ray_vector->end->y
				- ray_vector->end->y % PIXEL_SIZE - 1;
		else
			ray_vector->end->y = ray_vector->end->y - PIXEL_SIZE - 1;
	}
	else if (ray_info->quarter_angle > corner_angle)
	{
		if (ray_vector->end->x % PIXEL_SIZE)
			ray_vector->end->x = ray_vector->end->x
				- ray_vector->end->x % PIXEL_SIZE - 1;
		else
			ray_vector->end->x = ray_vector->end->x - PIXEL_SIZE - 1;
		ray_vector->end->y -= delta;
	}
}

static void	paint_append_vector_3(t_vector *ray_vector, t_ray *ray_info,
					double corner_angle, int delta)
{
	if (ray_info->quarter_angle <= corner_angle)
	{
		ray_vector->end->x -= delta;
		if (ray_vector->end->y % PIXEL_SIZE)
			ray_vector->end->y = ray_vector->end->y
				- ray_vector->end->y % PIXEL_SIZE + PIXEL_SIZE;
		else
			ray_vector->end->y += PIXEL_SIZE;
	}
	else if (ray_info->quarter_angle > corner_angle)
	{
		if (ray_vector->end->x % PIXEL_SIZE)
			ray_vector->end->x = ray_vector->end->x
				- ray_vector->end->x % PIXEL_SIZE - 1;
		else
			ray_vector->end->x = ray_vector->end->x - PIXEL_SIZE - 1;
		ray_vector->end->y += delta;
	}
}

static void	paint_append_vector_2(t_vector *ray_vector, t_ray *ray_info,
					double corner_angle, int delta)
{
	if (ray_info->quarter_angle <= corner_angle)
	{
		ray_vector->end->x += delta;
		if (ray_vector->end->y % PIXEL_SIZE)
			ray_vector->end->y = ray_vector->end->y
				- ray_vector->end->y % PIXEL_SIZE + PIXEL_SIZE;
		else
			ray_vector->end->y += PIXEL_SIZE;
	}
	else if (ray_info->quarter_angle > corner_angle)
	{
		if (ray_vector->end->x % PIXEL_SIZE)
			ray_vector->end->x = ray_vector->end->x
				- ray_vector->end->x % PIXEL_SIZE + PIXEL_SIZE;
		else
			ray_vector->end->x = ray_vector->end->x + PIXEL_SIZE;
		ray_vector->end->y += delta;
	}
}

static void	paint_append_vector_1(t_vector *ray_vector, t_ray *ray_info,
					double corner_angle, int delta)
{
	if (ray_info->quarter_angle <= corner_angle)
	{
		ray_vector->end->x += delta;
		if (ray_vector->end->y % PIXEL_SIZE)
			ray_vector->end->y = ray_vector->end->y
				- ray_vector->end->y % PIXEL_SIZE - 1;
		else
			ray_vector->end->y = ray_vector->end->y - PIXEL_SIZE - 1;
	}
	else if (ray_info->quarter_angle > corner_angle)
	{
		if (ray_vector->end->x % PIXEL_SIZE)
			ray_vector->end->x = ray_vector->end->x
				- ray_vector->end->x % PIXEL_SIZE + PIXEL_SIZE;
		else
			ray_vector->end->x += PIXEL_SIZE;
		ray_vector->end->y -= delta;
	}
}

static int	paint_append_vector(t_vector *ray_vector, t_ray *ray_info,
					double corner_angle, int delta)
{
	if (!ray_vector || !ray_info)
		return (1);
	if (ray_info->quarter == 1)
		paint_append_vector_1(ray_vector, ray_info, corner_angle, delta);
	else if (ray_info->quarter == 2)
		paint_append_vector_2(ray_vector, ray_info, corner_angle, delta);
	else if (ray_info->quarter == 3)
		paint_append_vector_3(ray_vector, ray_info, corner_angle, delta);
	else if (ray_info->quarter == 4)
		paint_append_vector_4(ray_vector, ray_info, corner_angle, delta);
	return (0);
}

static int	paint_is_wall(t_painting *painting, int pixel_x, int pixel_y)
{
	pixel_x -= pixel_x % PIXEL_SIZE;
	pixel_y -= pixel_y % PIXEL_SIZE;
	pixel_x /= PIXEL_SIZE;
	pixel_y /= PIXEL_SIZE;
	if (painting->map->lines[pixel_y]->line[pixel_x]->type == WALL)
		return (1);
	return (0);
}

static t_vector	*paint_init_ray_vector(t_painting *painting)
{
	t_point		*begin;
	t_point		*end;
	t_vector	*vector;

	if (!painting)
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
	vector = geom_init_vector(begin, end);
	if (vector)
		return (vector);
	geom_destroy_point(begin);
	geom_destroy_point(end);
	return (NULL);
}

static int	paint_get_delta_and_angle(double *corner_angle, int *delta,
					t_ray *ray_info, t_point *begin)
{
	t_vector	*corner_vector;

	if (!corner_angle || !delta || !ray_info)
		return (1);
	corner_vector = paint_get_corner_vector(begin, ray_info->quarter);
	if (!corner_vector)
		return (1);
	*corner_angle = geom_get_angle(ray_info->orient_vert, corner_vector);
	if (*corner_angle > 90.0)
		*corner_angle -= 90.0;
	if (ray_info->quarter_angle <= *corner_angle)
		*delta = sqrt(pow(corner_vector->begin->y - corner_vector->end->y, 2))
			* tan(ray_info->quarter_angle * M_PI / 180.0);
	else
		*delta = sqrt(pow(corner_vector->begin->x - corner_vector->end->x, 2))
			* tan((90 - ray_info->quarter_angle) * M_PI / 180.0);
	geom_destroy_vector(corner_vector);
	return (0);
}

static t_vector	*paint_get_ray_vector(t_painting *painting, t_ray *ray_info)
{	
	int			delta;
	double		corner_angle;
	t_vector	*ray_vector;

	if (!painting || !ray_info)
		return (NULL);
	ray_vector = paint_init_ray_vector(painting);
	if (!ray_vector)
		return (NULL);
	while (1)
	{
		if (paint_get_delta_and_angle(&corner_angle, &delta,
				ray_info, ray_vector->end)
			|| paint_append_vector(ray_vector, ray_info,
				corner_angle, delta))
		{
			geom_destroy_vector(ray_vector);
			return (NULL);
		}
		if (paint_is_wall(painting, ray_vector->end->x, ray_vector->end->y))
		{
			break ;
		}
	}	
	return (ray_vector);
}

void	paint_print_ray(t_painting *painting)
{
	t_ray			*ray_info;
	static t_vector	*ray_vector = NULL;
	static t_vector	*ray_vector_prev = NULL;

	if (!painting)
		return ;
	ray_info = paint_get_ray_info(painting);
	if (!ray_info)
		return ;
	ray_vector = paint_get_ray_vector(painting, ray_info);
	if (!ray_vector)
	{
		paint_destroy_ray_info(ray_info);
		return ;
	}
	paint_erase_vector(painting, ray_vector_prev);
	paint_draw_vector(painting, ray_vector);
	ray_vector_prev = ray_vector;
	paint_destroy_ray_info(ray_info);
}
