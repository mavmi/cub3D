/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_minimap_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:33:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/05 20:51:58 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

void	paint_minimap_draw_map(t_painting *painting)
{
	char	t;
	size_t	x;
	size_t	y;
	size_t	sq_x;
	size_t	sq_y;

	if (!painting)
		return ;
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		sq_y = (y - y % MAP_SQ_SIZE) / MAP_SQ_SIZE;
		while (x < MAP_WIDTH)
		{
			sq_x = (x - x % MAP_SQ_SIZE) / MAP_SQ_SIZE;
			if (sq_y < painting->map->height && sq_x < painting->map->lines[sq_y]->width)
			{
				t = painting->map->lines[sq_y]->line[sq_x]->type;
				if (t != MAP_SQ_VOID && (!(x % MAP_SQ_SIZE) || !(y % MAP_SQ_SIZE)))
					paint_put_pixel(&painting->minimap, x, y, COLOR_GRID);
				else if (t == MAP_SQ_WALL)
					paint_put_pixel(&painting->minimap, x, y, COLOR_WALL);
				else if (t == MAP_SQ_EMPTY)
					paint_put_pixel(&painting->minimap, x, y, COLOR_FIELD);
				else if (t == MAP_SQ_VOID)
					paint_put_pixel(&painting->minimap, x, y, COLOR_TRANSPARENT);
			}
			else
				paint_put_pixel(&painting->minimap, x, y, COLOR_TRANSPARENT);
			x++;
		}
		y++;
	}
	paint_minimap_draw_player(painting);
	mlx_put_image_to_window(painting->mlx, painting->win,
		painting->minimap.img, 0, 0);
}
