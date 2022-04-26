/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_room_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:29:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/19 15:12:25 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

/*
	Just initialization of t_room_vars
*/
static t_room_vars	paint_room_get_data(t_painting *painting)
{
	t_room_vars	room_data;

	room_data.x = 0;
	room_data.y = 0;
	room_data.wall_start = 0;
	room_data.wall_end = 0;
	room_data.wall_height = 0;
	room_data.ray_len = 0.0;
	room_data.angle_delta = FOV / WIN_WIDTH;
	room_data.angle = paint_room_decrease_angle(painting->map->player->angle,
			FOV / 2);
	return (room_data);
}

/*
	Get image of wall
*/
static t_image	*paint_room_get_image(t_painting *painting, t_orient orient)
{
	static size_t	gif_count = 0;

	if (orient == ORIENT_NORTH)
		return (painting->t_north);
	if (orient == ORIENT_EAST)
		return (painting->t_east);
	if (orient == ORIENT_SOUTH)
		return (painting->t_south);
	if (orient == ORIENT_WEST)
		return (painting->t_west);
	if (orient == ORIENT_CL_DOOR)
		return (painting->t_door);
	if (orient == ORIENT_GIF)
	{
		if (gif_count == 9000)
			gif_count = 0;
		return (painting->t_gif[gif_count++ / 1000]);
	}
	else
		return (NULL);
}

/*
	Update [data] for new angle of view
*/
static int	paint_room_update_vars(t_room_vars *data, t_painting *painting)
{
	double	val;

	data->ray_of_view = paint_ray_get_ray_of_view(painting, data->angle);
	if (!data->ray_of_view)
		return (1);
	data->ray_len = geom_vector_get_module(data->ray_of_view->ray);
	data->image = paint_room_get_image(painting, data->ray_of_view->orient);
	if (!utils_is_double_integer(data->ray_of_view->ray->end->x))
		val = data->ray_of_view->ray->end->x;
	else
		val = data->ray_of_view->ray->end->y;
	data->text_x = data->image->w * (val - (int)val);
	data->text_y = 0;
	paint_ray_destroy_ray_of_view(data->ray_of_view);
	data->angle = paint_room_increase_angle(data->angle, data->angle_delta);
	data->wall_height = WIN_HEIGHT / data->ray_len;
	data->wall_start = WIN_HEIGHT / 2 - data->wall_height / 2;
	if (data->wall_start < 0)
		data->wall_start = 0;
	data->wall_end = WIN_HEIGHT / 2 + data->wall_height / 2;
	if (data->wall_end >= WIN_HEIGHT)
		data->wall_end = WIN_HEIGHT;
	data->y = 0;
	return (0);
}

/*
	Get pixel from image
*/
static int	paint_room_get_pixel(t_image *image, int x, int y)
{
	int			pos;

	pos = y * image->drawable.size_line
		+ x * (image->drawable.bits_per_pixel / 8);
	return (*(int *)(image->drawable.img_addr + pos));
}

/*
	Draw room.
	Return 0 if everything is ok,
	1 otherwise
*/
int	paint_room_draw_room(t_painting *p)
{
	double		delta;
	t_room_vars	data;

	data = paint_room_get_data(p);
	while (data.x < WIN_WIDTH)
	{
		if (paint_room_update_vars(&data, p))
			return (1);
		while (data.y < data.wall_start)
			paint_put_pixel(&p->room, data.x, data.y++, p->ceil);
		delta = data.image->h / (double)data.wall_height;
		while (data.y < data.wall_end)
		{
			paint_put_pixel(&p->room, data.x, data.y++,
				paint_room_get_pixel(data.image, data.text_x, data.text_y));
			data.text_y += delta;
		}
		while (data.y < WIN_HEIGHT)
			paint_put_pixel(&p->room, data.x, data.y++, p->floor);
		data.x++;
	}
	mlx_put_image_to_window(p->mlx, p->win, p->room.img, 0, 0);
	return (0);
}
