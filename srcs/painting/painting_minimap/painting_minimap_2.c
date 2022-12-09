/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_minimap_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:32:43 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/19 14:36:57 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

/*
	Draw player's circle or background.
	It all depends on {x, y} point of current pixel
*/
static void	paint_minimap_draw_player_handler(t_painting *painting,
						int x, int y, t_color color)
{
	if (paint_get_dist(
			x, y,
			painting->map->player->pos->x * MAP_SQ_SIZE - painting->minimap_x,
			painting->map->player->pos->y * MAP_SQ_SIZE - painting->minimap_y
		) < MAP_PL_RAD * MAP_SQ_SIZE)
		paint_put_color(&painting->minimap, x, y, color);
	if (color != COLOR_FIELD)
		return ;
	if ((x + painting->minimap_x) % MAP_SQ_SIZE == 0
		|| (y + painting->minimap_y) % MAP_SQ_SIZE == 0)
		paint_put_color(&painting->minimap, x, y, COLOR_GRID);
	else if (painting->map->lines[((y + painting->minimap_y)
				- (y + painting->minimap_y) % MAP_SQ_SIZE) / MAP_SQ_SIZE]
		-> line[((x + painting->minimap_x) - (x + painting->minimap_x)
				% MAP_SQ_SIZE) / MAP_SQ_SIZE]->type == MAP_SQ_OP_DOOR)
		paint_put_color(&painting->minimap, x, y, COLOR_DOOR);
	else
		paint_put_color(&painting->minimap, x, y, COLOR_FIELD);
}

/*
	Draw player with specified color
*/
static void	paint_minimap_player_printer(t_painting *painting, t_color color)
{
	int	iter_x;
	int	iter_y;
	int	tl_x;
	int	tl_y;

	if (!painting)
		return ;
	tl_x = (painting->map->player->pos->x - MAP_PL_RAD) * MAP_SQ_SIZE
		- painting->minimap_x;
	tl_y = (painting->map->player->pos->y - MAP_PL_RAD) * MAP_SQ_SIZE
		- painting->minimap_y;
	iter_y = 0;
	while (iter_y < (int)(2 * MAP_PL_RAD * MAP_SQ_SIZE))
	{
		iter_x = 0;
		while (iter_x < (int)(2 * MAP_PL_RAD * MAP_SQ_SIZE))
		{
			paint_minimap_draw_player_handler(painting, tl_x + iter_x,
				tl_y + iter_y, color);
			iter_x++;
		}
		iter_y++;
	}
}

/*
	Draw player in minimap
*/
void	paint_minimap_draw_player(t_painting *painting)
{
	if (!painting)
		return ;
	paint_minimap_player_printer(painting, COLOR_PLAYER);
}

/*
	Delete player from minimap
*/
void	paint_minimap_erase_player(t_painting *painting)
{
	if (!painting)
		return ;
	paint_minimap_player_printer(painting, COLOR_FIELD);
}
