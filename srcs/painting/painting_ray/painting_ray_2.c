/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:36:50 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/08 16:59:47 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

/*
	\ (•◡•) /
*/
void	paint_ray_destroy_ray_info(t_ray *ray)
{
	if (!ray)
		return ;
	geom_destroy_vector(ray->orient_vert);
	geom_destroy_vector(ray->orient_hor);
	free(ray);
}

/*
	Update t_ray's orientation vectors 
	depending on it's quarter.
	Return 0 if everything is fine,
	1 otherwise
*/
static int	paint_ray_get_ray_info_handler(t_ray *ray)
{
	if (!ray)
		return (1);
	if (ray->quarter == 1)
	{
		ray->orient_vert = paint_ray_get_orient_vector(ORIENT_NORTH);
		ray->orient_hor = paint_ray_get_orient_vector(ORIENT_EAST);
	}
	else if (ray->quarter == 2)
	{
		ray->orient_vert = paint_ray_get_orient_vector(ORIENT_SOUTH);
		ray->orient_hor = paint_ray_get_orient_vector(ORIENT_EAST);
	}
	else if (ray->quarter == 3)
	{
		ray->orient_vert = paint_ray_get_orient_vector(ORIENT_SOUTH);
		ray->orient_hor = paint_ray_get_orient_vector(ORIENT_WEST);
	}
	else if (ray->quarter == 4)
	{
		ray->orient_vert = paint_ray_get_orient_vector(ORIENT_NORTH);
		ray->orient_hor = paint_ray_get_orient_vector(ORIENT_WEST);
	}
	if (!ray->orient_vert || !ray->orient_hor)
		return (1);
	return (0);
}

/*
	Create t_ray struct of player's vector of view.
	
	May return NULL
*/
t_ray	*paint_ray_get_ray_info(double angle)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->quarter = paint_ray_get_quarter(angle);
	ray->quarter_angle = paint_ray_get_quarter_angle(ray->quarter, angle);
	if (utils_are_doubles_equal(ray->quarter_angle, -1.0)
		|| paint_ray_get_ray_info_handler(ray))
	{
		paint_ray_destroy_ray_info(ray);
		return (NULL);
	}
	return (ray);
}
