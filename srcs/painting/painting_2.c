/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <username@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:33:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/26 00:37:54 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

// Draw one pixel with defined size PIXEL_SIZE.
// {x, y} is absolute position of current pixel
// relative map's array of strings
void	paint_draw_pixel(t_painting *painting,
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
				mlx_pixel_put(painting->mlx, painting->win,
					x + x_iter, y + y_iter, paint_get_color(COLOR_GRID));
			else
				mlx_pixel_put(painting->mlx, painting->win,
					x + x_iter, y + y_iter, paint_get_color(color));
			x_iter++;
		}
		y_iter++;
	}
}

// Draw player's circle or background.
// It all depends on {x, y} point of current pixel
static void	paint_draw_player_handler(t_painting *painting,
						int x, int y, t_color color)
{
	if (paint_get_dist(
			x, y,
			painting->map->player->pos->x * PIXEL_SIZE,
			painting->map->player->pos->y * PIXEL_SIZE
		) < PLAYER_RAD * PIXEL_SIZE)
		mlx_pixel_put(painting->mlx, painting->win, x, y,
			paint_get_color(color));
	if (color != COLOR_FIELD)
		return ;
	if (x % PIXEL_SIZE == 0 || y % PIXEL_SIZE == 0)
		mlx_pixel_put(painting->mlx, painting->win,
			x, y, paint_get_color(COLOR_GRID));
	else
		mlx_pixel_put(painting->mlx, painting->win,
			x, y, paint_get_color(COLOR_FIELD));
}

// Draw player with specified color
void	paint_draw_player(t_painting *painting, t_color color)
{
	int	iter_x;
	int	iter_y;
	int	tl_x;
	int	tl_y;

	if (!painting)
		return ;
	tl_x = ((double)painting->map->player->pos->x - PLAYER_RAD) * PIXEL_SIZE;
	tl_y = ((double)painting->map->player->pos->y - PLAYER_RAD) * PIXEL_SIZE;
	iter_y = 0;
	while (iter_y < (int)(2 * PLAYER_RAD * PIXEL_SIZE))
	{
		iter_x = 0;
		while (iter_x < (int)(2 * PLAYER_RAD * PIXEL_SIZE))
		{
			paint_draw_player_handler(painting, tl_x + iter_x,
				tl_y + iter_y, color);
			iter_x++;
		}
		iter_y++;
	}
}

// Draw whole map without player and vectors of view
void	paint_draw_map(t_painting *painting)
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
			if (painting->map->lines[y]->line[x]->type == WALL)
				paint_draw_pixel(painting, x, y, COLOR_WALL);
			else
				paint_draw_pixel(painting, x, y, COLOR_FIELD);
			x++;
		}
		y++;
	}
}
