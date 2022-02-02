/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_minimap_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:32:43 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 12:33:34 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

// Draw player's circle or background.
// It all depends on {x, y} point of current pixel
static void	paint_minimap_draw_player_handler(t_painting *painting,
						int x, int y, t_color color)
{
	if (paint_get_dist(
			x, y,
			painting->map->player->pos->x * PIXEL_SIZE,
			painting->map->player->pos->y * PIXEL_SIZE
		) < PL_RAD * PIXEL_SIZE)
		paint_put_pixel(painting, x, y, color);
	if (color != COLOR_FIELD)
		return ;
	if (x % PIXEL_SIZE == 0 || y % PIXEL_SIZE == 0)
		paint_put_pixel(painting, x, y, COLOR_GRID);
	else
		paint_put_pixel(painting, x, y, COLOR_FIELD);
}

// Draw player with specified color
static void	paint_minimap_player_printer(t_painting *painting, t_color color)
{
	int	iter_x;
	int	iter_y;
	int	tl_x;
	int	tl_y;

	if (!painting)
		return ;
	tl_x = ((double)painting->map->player->pos->x - PL_RAD) * PIXEL_SIZE;
	tl_y = ((double)painting->map->player->pos->y - PL_RAD) * PIXEL_SIZE;
	iter_y = 0;
	while (iter_y < (int)(2 * PL_RAD * PIXEL_SIZE))
	{
		iter_x = 0;
		while (iter_x < (int)(2 * PL_RAD * PIXEL_SIZE))
		{
			paint_minimap_draw_player_handler(painting, tl_x + iter_x,
				tl_y + iter_y, color);
			iter_x++;
		}
		iter_y++;
	}
}

// Draw player in canvas
void	paint_minimap_draw_player(t_painting *painting)
{
	if (!painting)
		return ;
	paint_minimap_player_printer(painting, COLOR_PLAYER);
}

// Delete player from canvas
void	paint_minimap_erase_player(t_painting *painting)
{
	if (!painting)
		return ;
	paint_minimap_player_printer(painting, COLOR_FIELD);
}
