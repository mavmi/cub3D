/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_movements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:36:15 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/14 16:50:44 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

static t_movements	paint_get_vars(t_painting *painting)
{
	t_movements	vars;

	vars.sq_x = painting->map->player->pos->x;
	vars.sq_y = painting->map->player->pos->y;
	vars.pl_x = painting->map->player->pos->x;
	vars.pl_y = painting->map->player->pos->y;
	return (vars);
}

void	paint_move_left(t_painting *painting)
{
	t_movements	vars;

	vars = paint_get_vars(painting);
	if (painting->map->lines[vars.sq_y]->line[vars.sq_x - 1]->type != WALL
		|| paint_get_dist(vars.pl_x, vars.pl_y,
			vars.sq_x, vars.pl_y) - PLAYER_RAD > EPS)
	{
		painting->map->player->pos->x -= STEP;
	}
}

void	paint_move_right(t_painting *painting)
{
	t_movements	vars;

	vars = paint_get_vars(painting);
	if (painting->map->lines[vars.sq_y]->line[vars.sq_x + 1]->type != WALL
		|| paint_get_dist(vars.pl_x, vars.pl_y,
			vars.sq_x + 1, vars.pl_y) - PLAYER_RAD > EPS)
	{
		painting->map->player->pos->x += STEP;
	}
}

void	paint_move_up(t_painting *painting)
{
	t_movements	vars;

	vars = paint_get_vars(painting);
	if (painting->map->lines[vars.sq_y - 1]->line[vars.sq_x]->type != WALL
		|| paint_get_dist(vars.pl_x, vars.pl_y,
			vars.pl_x, vars.sq_y) - PLAYER_RAD > EPS)
	{
		painting->map->player->pos->y -= STEP;
	}
}

void	paint_move_down(t_painting *painting)
{
	t_movements	vars;

	vars = paint_get_vars(painting);
	if (painting->map->lines[vars.sq_y + 1]->line[vars.sq_x]->type != WALL
		|| paint_get_dist(vars.pl_x, vars.pl_y,
			vars.pl_x, vars.sq_y + 1) - PLAYER_RAD > EPS)
	{
		painting->map->player->pos->y += STEP;
	}
}
