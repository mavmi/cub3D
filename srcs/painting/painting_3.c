/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:29:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/30 16:34:09 by pmaryjo          ###   ########.fr       */
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
	return (delta - (360.0 - angle));
}

static t_color	paint_get_color_from_orien(t_orient orient)
{
	if (orient == ORIENT_NORTH)
		return ((COLOR_NORTH));
	if (orient == ORIENT_SOUTH)
		return ((COLOR_SOUTH));
	if (orient == ORIENT_EAST)
		return ((COLOR_EAST));
	if (orient == ORIENT_WEST)
		return ((COLOR_WEST));
	return ((COLOR_GREEN));
}

int	paint_draw_room(t_painting *painting)
{
	int				x;
	int				y;
	int				height;
	double			len;
	double			angle;
	double			angle_delta;
	t_ray_of_view	*ray_of_view;
	
	angle = paint_decrease_angle(painting->map->player->angle, FOV / 2);
	angle_delta = FOV / WIDTH;
	x = 0;
	while (x++ < WIDTH)
	{
		ray_of_view = paint_get_ray_of_view(painting, angle);
		if (!ray_of_view)
			return (1);
		len = geom_vector_get_module(ray_of_view->ray_of_view);
		paint_destroy_ray_of_view(ray_of_view);
		angle = paint_increase_angle(angle, angle_delta);
		height = HEIGHT / len;
		y = 0;
		while (y < HEIGHT / 2 - height / 2)
			paint_put_pixel(painting, x, y++, COLOR_BLACK);
		while (y < HEIGHT / 2 - height / 2 + height)
			paint_put_pixel(painting, x, y++, 
				paint_get_color_from_orien(ray_of_view->orient));
		while (y < HEIGHT)
			paint_put_pixel(painting, x, y++, COLOR_BLACK);
	}
	mlx_put_image_to_window(painting->mlx, painting->win, painting->img, 0, 0);
	return (0);
}
