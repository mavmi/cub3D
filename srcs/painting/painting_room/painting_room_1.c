/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_room_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:29:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 14:24:24 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

static t_room_data	paint_room_get_data(t_painting *painting)
{
	t_room_data	room_data;

	room_data.x = 0;
	room_data.y = 0;
	room_data.height = 0;
	room_data.len = 0.0;
	room_data.angle = paint_room_decrease_angle(painting->map->player->angle,
			FOV / 2);
	room_data.angle_delta = FOV / WIDTH;
	return (room_data);
}

int	paint_room_draw_room(t_painting *painting)
{
	t_room_data	data;

	data = paint_room_get_data(painting);
	while (data.x++ < WIDTH)
	{
		data.ray_of_view = paint_get_ray_of_view(painting, data.angle);
		if (!data.ray_of_view)
			return (1);
		data.len = geom_vector_get_module(data.ray_of_view->ray);
		paint_destroy_ray_of_view(data.ray_of_view);
		data.angle = paint_room_increase_angle(data.angle, data.angle_delta);
		data.height = HEIGHT / data.len;
		data.y = 0;
		while (data.y < HEIGHT / 2 - data.height / 2)
			paint_put_pixel(painting, data.x, data.y++, COLOR_BLACK);
		while (data.y < HEIGHT / 2 - data.height / 2 + data.height)
			paint_put_pixel(painting, data.x, data.y++,
				paint_room_get_color_from_orien(data.ray_of_view->orient));
		while (data.y < HEIGHT)
			paint_put_pixel(painting, data.x, data.y++, COLOR_BLACK);
	}
	mlx_put_image_to_window(painting->mlx, painting->win, painting->img, 0, 0);
	return (0);
}
