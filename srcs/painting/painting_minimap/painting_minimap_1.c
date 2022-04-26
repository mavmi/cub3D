/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_minimap_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:33:39 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/13 20:11:57 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

/*
	Get color of minimap's square
*/
static t_color	paint_minimap_type_to_color(char type)
{
	if (type == MAP_SQ_WALL)
		return (COLOR_WALL);
	else if (type == MAP_SQ_EMPTY)
		return (COLOR_FIELD);
	else if (type == MAP_SQ_CL_DOOR || type == MAP_SQ_OP_DOOR)
		return (COLOR_DOOR);
	else if (type == MAP_SQ_GIF)
		return (COLOR_GIF);
	else
		return (COLOR_TRANSPARENT);
}

/*
	Draw minimap's line
*/
static void	paint_minimap_draw_map_line(t_painting *painting,
				size_t sq_y, size_t abs_y, size_t y)
{
	char	t;
	size_t	x;
	size_t	sq_x;
	size_t	abs_x;

	x = 0;
	while (x < MAP_WIDTH)
	{
		abs_x = x + painting->minimap_x;
		sq_x = (abs_x - abs_x % MAP_SQ_SIZE) / MAP_SQ_SIZE;
		if (sq_y < painting->map->height
			&& sq_x < painting->map->lines[sq_y]->width)
		{
			t = painting->map->lines[sq_y]->line[sq_x]->type;
			if (t != MAP_SQ_VOID && (!(abs_x % MAP_SQ_SIZE)
					|| !(abs_y % MAP_SQ_SIZE)))
				paint_put_color(&painting->minimap, x, y, COLOR_GRID);
			else
				paint_put_color(&painting->minimap, x, y,
					paint_minimap_type_to_color(t));
		}
		else
			paint_put_color(&painting->minimap, x, y, COLOR_TRANSPARENT);
		x++;
	}
}

/*
	Just draw minimap
*/
void	paint_minimap_draw_map(t_painting *painting)
{
	size_t	y;
	size_t	sq_y;
	size_t	abs_y;

	if (!painting)
		return ;
	y = 0;
	while (y < MAP_HEIGHT)
	{
		abs_y = y + painting->minimap_y;
		sq_y = (abs_y - abs_y % MAP_SQ_SIZE) / MAP_SQ_SIZE;
		paint_minimap_draw_map_line(painting, sq_y, abs_y, y);
		y++;
	}
}

/*
	Check if it is necessary to redraw minimap
*/
static int	paint_minimap_is_redraw(t_painting *painting,
				int pl_sq_x, int pl_sq_y, int rad)
{
	if (!(pl_sq_x < painting->minimap_x
			|| pl_sq_x + rad > painting->minimap_x + MAP_WIDTH
			|| pl_sq_y < painting->minimap_y
			|| pl_sq_y + rad > painting->minimap_y + MAP_HEIGHT))
		return (0);
	if (pl_sq_x < painting->minimap_x)
	{
		if (painting->minimap_x > MAP_DELTA)
			painting->minimap_x -= MAP_DELTA;
		else
			painting->minimap_x = 0;
	}
	else if (pl_sq_x + rad > painting->minimap_x + MAP_WIDTH)
		painting->minimap_x += MAP_DELTA;
	if (pl_sq_y < painting->minimap_y)
	{
		if (painting->minimap_y > MAP_DELTA)
			painting->minimap_y -= MAP_DELTA;
		else
			painting->minimap_y = 0;
	}
	else if (pl_sq_y + rad > painting->minimap_y + MAP_HEIGHT)
		painting->minimap_y += MAP_DELTA;
	return (1);
}

/*
	Redraw minimap if it is necessary and draw player
*/
void	paint_minimap_draw(t_painting *painting)
{
	int	pl_sq_x;
	int	pl_sq_y;
	int	delta;
	int	rad;

	if (!painting)
		return ;
	pl_sq_x = (int)painting->map->player->pos->x * MAP_SQ_SIZE;
	pl_sq_y = (int)painting->map->player->pos->y * MAP_SQ_SIZE;
	delta = 100;
	rad = MAP_PL_RAD * MAP_SQ_SIZE * 2;
	if (paint_minimap_is_redraw(painting, pl_sq_x, pl_sq_y, rad))
		paint_minimap_draw_map(painting);
	paint_minimap_draw_player(painting);
	mlx_put_image_to_window(painting->mlx, painting->win,
		painting->minimap.img, 0, 0);
}
