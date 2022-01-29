/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:29:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/29 18:30:51 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

static double	paint_decrease_angle(double angle, double delta)
{
	if (angle > delta)
		return (angle - delta);
	return (360.0 - (sqrt(pow(angle - delta, 2))));
}

static double	paint_increase_angle(double angle, double delta)
{
	if (angle + delta < 360.0)
		return (angle + delta);
	return (sqrt(pow(angle - delta, 2)));
}

int	paint_draw_room(t_painting *painting)
{
	int			i;
	int			iters;
	double		len;
	double		angle;
	double		angle_delta;
	t_vector	*ray;
	
	angle = paint_decrease_angle(painting->map->player->angle, FOV / 2);
	angle_delta = 1.0;
	iters = FOV / angle_delta;
	i = 0;
	while (i++ < iters)
	{
		ray = paint_get_ray_of_view(painting, angle);
		if (!ray)
			return (1);
		len = geom_vector_get_module(ray);
		geom_destroy_vector(ray);
		angle = paint_increase_angle(angle, angle_delta);
	}
	return (0);
}
