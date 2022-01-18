/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:36:50 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/18 19:11:04 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

void	paint_destroy_ray_info(t_ray *ray)
{
	if (!ray)
		return ;
	geom_destroy_vector(ray->orient_vector);
	free(ray);
}

static int	paint_get_quarter(int angle)
{
	if (angle == 360 || (angle >= 0 && angle < 90))
		return (1);
	if (angle >= 90 && angle < 180)
		return (2);
	if (angle >= 180 && angle < 270)
		return (3);
	if (angle >= 270 && angle < 360)
		return (4);
	return (0);
}

static int	paint_get_quarter_angle(int quarter, int abs_angle)
{
	if (quarter == 1)
		return (abs_angle);
	if (quarter == 2)
		return (abs_angle - 90);
	if (quarter == 3)
		return (abs_angle - 180);
	if (quarter == 4)
		return (abs_angle - 270);
	return (-1);
}

static t_vector	*paint_get_orient_vector(int quarter)
{
	t_point		*begin;
	t_point		*end;
	t_vector	*orient_vector;

	if (quarter < 1 || quarter > 4)
		return (NULL);
	begin = geom_init_point(0, 0, 0);
	if (!begin)
		return (NULL);
	if (quarter == 1)
		end = geom_init_point(0, 1, 0);
	else if (quarter == 2)
		end = geom_init_point(1, 0, 0);
	else if (quarter == 3)
		end = geom_init_point(0, -1, 0);
	else
		end = geom_init_point(-1, 0, 0);
	if (!end)
		return (NULL);
	orient_vector = geom_init_vector(begin, end);
	if (orient_vector)
		return (orient_vector);
	geom_destroy_point(begin);
	geom_destroy_point(end);
	return (NULL);
}

t_ray	*paint_get_ray_info(t_painting *painting)
{
	t_ray	*ray;

	if (!painting)
		return (NULL);
	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->quarter = paint_get_quarter(painting->map->player->angle);
	ray->quarter_angle = paint_get_quarter_angle(ray->quarter,
			painting->map->player->angle);
	ray->orient_vector = paint_get_orient_vector(ray->quarter);
	if (!ray->orient_vector || ray->quarter_angle == -1)
	{
		paint_destroy_ray_info(ray);
		return (NULL);
	}
	return (ray);
}
