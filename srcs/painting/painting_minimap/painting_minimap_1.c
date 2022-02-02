/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_minimap_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:33:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 12:33:20 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

// Draw one pixel with defined size PIXEL_SIZE.
// {x, y} is absolute position of current pixel
// relative map's array of strings
void	paint_minimap_draw_pixel(t_painting *painting,
						size_t x, size_t y, t_color color)
{
	int	x_iter;
	int	y_iter;

	if (!painting || x < 0 || y < 0)
		return ;
	x *= PIXEL_SIZE;
	y *= PIXEL_SIZE;
	y_iter = 0;
	while (y_iter < PIXEL_SIZE)
	{
		x_iter = 0;
		while (x_iter < PIXEL_SIZE)
		{
			if ((x + x_iter) % PIXEL_SIZE == 0
				|| (y + y_iter) % PIXEL_SIZE == 0)
				paint_put_pixel(painting, x + x_iter, y + y_iter, COLOR_GRID);
			else
				paint_put_pixel(painting, x + x_iter, y + y_iter, color);
			x_iter++;
		}
		y_iter++;
	}
}

// Draw whole map without any additional stuff
void	paint_minimap_draw_map(t_painting *painting)
{
	size_t	x;
	size_t	y;

	if (!painting)
		return ;
	y = 0;
	while (y < painting->map->height)
	{
		x = 0;
		while (x < painting->map->lines[y]->width)
		{
			if (painting->map->lines[y]->line[x]->type == MAP_SQ_WALL)
				paint_minimap_draw_pixel(painting, x, y, COLOR_WALL);
			else
				paint_minimap_draw_pixel(painting, x, y, COLOR_FIELD);
			x++;
		}
		y++;
	}
}
