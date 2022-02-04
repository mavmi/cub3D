/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_room_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:29:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/04 15:06:39 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

static t_room_data	paint_room_get_data(t_painting *painting)
{
	t_room_data	room_data;

	room_data.x = 0;
	room_data.y = 0;
	room_data.wall_start = 0;
	room_data.wall_end = 0;
	room_data.wall_height = 0;
	room_data.ray_len = 0.0;
	room_data.angle_delta = FOV / WIDTH;
	room_data.angle = paint_room_decrease_angle(painting->map->player->angle,
			FOV / 2 + room_data.angle_delta);
	return (room_data);
}

static int	paint_room_update_vars(t_room_data *data, t_painting *painting)
{
	data->ray_of_view = paint_ray_get_ray_of_view(painting, data->angle);
	if (!data->ray_of_view)
		return (1);
	data->ray_len = geom_vector_get_module(data->ray_of_view->ray);
	paint_ray_destroy_ray_of_view(data->ray_of_view);
	data->angle = paint_room_increase_angle(data->angle, data->angle_delta);
	data->wall_height = HEIGHT / data->ray_len;
	data->wall_start = HEIGHT / 2 - data->wall_height / 2;
	if (data->wall_start < 0)
		data->wall_start = 0;
	data->wall_end = HEIGHT / 2 + data->wall_height / 2;
	if (data->wall_end >= HEIGHT)
		data->wall_end = HEIGHT;
	data->y = 0;
	return (0);
}

int	paint_room_draw_room(t_painting *painting)
{
	t_room_data	data;

	data = paint_room_get_data(painting);
	while (data.x < WIDTH)
	{
		if (paint_room_update_vars(&data, painting))
			return (1);
		while (data.y < data.wall_start)
			paint_put_pixel(painting, data.x, data.y++, COLOR_BLACK);
		while (data.y < data.wall_end)
			paint_put_pixel(painting, data.x, data.y++,
				paint_room_orient_to_color(data.ray_of_view->orient));
		while (data.y < HEIGHT)
			paint_put_pixel(painting, data.x, data.y++, COLOR_BLACK);
		data.x++;
	}
	mlx_put_image_to_window(painting->mlx, painting->win, painting->img, 0, 0);
	return (0);
}
