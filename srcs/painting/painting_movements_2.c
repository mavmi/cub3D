/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_movements_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:20:24 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/27 19:21:02 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

// Create t_movements struct to handle current movement.
// It's just easier to contain all of them inside only one struct
static t_movements	paint_get_vars(t_painting *p)
{
	t_movements	vars;

	vars.tl_x = p->map->player->pos->x - PL_RAD;
	vars.tl_y = p->map->player->pos->y - PL_RAD;
	vars.bl_x = p->map->player->pos->x - PL_RAD;
	vars.bl_y = p->map->player->pos->y + PL_RAD;
	vars.tr_x = p->map->player->pos->x + PL_RAD;
	vars.tr_y = p->map->player->pos->y - PL_RAD;
	vars.br_x = p->map->player->pos->x + PL_RAD;
	vars.br_y = p->map->player->pos->y + PL_RAD;
	return (vars);
}

// All these functions just check if required movement is available and
// return 1 if it is, 0 otherwise

int	paint_is_move_left(t_painting *p)
{
	t_movements	v;

	v = paint_get_vars(p);
	if ((p->map->lines[(int)v.tl_y]->line[(int)v.tl_x - 1]->type != MAP_SQ_WALL
			|| paint_get_dist((int)v.tl_x, 0, v.tl_x, 0) > PL_STEP)
		&& (p->map->lines[(int)v.bl_y]->line[(int)v.bl_x - 1]
			->type != MAP_SQ_WALL
			|| paint_get_dist((int)v.bl_x, 0, v.bl_x, 0) > PL_STEP))
	{
		return (1);
	}
	return (0);
}

int	paint_is_move_right(t_painting *p)
{
	t_movements	v;

	v = paint_get_vars(p);
	if ((p->map->lines[(int)v.tr_y]->line[(int)v.tr_x + 1]->type != MAP_SQ_WALL
			|| paint_get_dist((int)v.tr_x + 1, 0, v.tr_x, 0) > PL_STEP)
		&& (p->map->lines[(int)v.br_y]->line[(int)v.br_x + 1]
			->type != MAP_SQ_WALL
			|| paint_get_dist((int)v.br_x + 1, 0, v.br_x, 0) > PL_STEP))
	{
		return (1);
	}
	return (0);
}

int	paint_is_move_up(t_painting *p)
{
	t_movements	v;

	v = paint_get_vars(p);
	if ((p->map->lines[(int)v.tr_y - 1]->line[(int)v.tr_x]->type != MAP_SQ_WALL
			|| paint_get_dist(0, (int)v.tr_y, 0, v.tr_y) > PL_STEP)
		&& (p->map->lines[(int)v.tl_y - 1]->line[(int)v.tl_x]
			->type != MAP_SQ_WALL
			|| paint_get_dist(0, (int)v.tl_y, 0, v.tl_y) > PL_STEP))
	{
		return (1);
	}
	return (0);
}

int	paint_is_move_down(t_painting *p)
{
	t_movements	v;

	v = paint_get_vars(p);
	if ((p->map->lines[(int)v.br_y + 1]->line[(int)v.br_x]->type != MAP_SQ_WALL
			|| paint_get_dist(0, (int)v.br_y + 1, 0, v.br_y) > PL_STEP)
		&& (p->map->lines[(int)v.bl_y + 1]->line[(int)v.bl_x]
			->type != MAP_SQ_WALL
			|| paint_get_dist(0, (int)v.bl_y + 1, 0, v.bl_y) > PL_STEP))
	{
		return (1);
	}
	return (0);
}
