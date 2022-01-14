/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_movements_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:20:24 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/14 20:07:22 by pmaryjo          ###   ########.fr       */
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

int	paint_is_move_left(t_painting *painting)
{
	t_movements	vars;

	vars = paint_get_vars(painting);
	if (painting->map->lines[vars.sq_y]->line[vars.sq_x - 1]->type != WALL
		|| (paint_get_dist(vars.pl_x, vars.pl_y,
				vars.sq_x, vars.pl_y) - PLAYER_RAD > EPS))
	{
		return (1);
	}
	return (0);
}

int	paint_is_move_right(t_painting *painting)
{
	t_movements	vars;

	vars = paint_get_vars(painting);
	if (painting->map->lines[vars.sq_y]->line[vars.sq_x + 1]->type != WALL
		|| paint_get_dist(vars.pl_x, vars.pl_y,
			vars.sq_x + 1, vars.pl_y) - PLAYER_RAD > EPS)
	{
		return (1);
	}
	return (0);
}

int	paint_is_move_up(t_painting *painting)
{
	t_movements	vars;

	vars = paint_get_vars(painting);
	if (painting->map->lines[vars.sq_y - 1]->line[vars.sq_x]->type != WALL
		|| paint_get_dist(vars.pl_x, vars.pl_y,
			vars.pl_x, vars.sq_y) - PLAYER_RAD > EPS)
	{
		return (1);
	}
	return (0);
}

int	paint_is_move_down(t_painting *painting)
{
	t_movements	vars;

	vars = paint_get_vars(painting);
	if (painting->map->lines[vars.sq_y + 1]->line[vars.sq_x]->type != WALL
		|| paint_get_dist(vars.pl_x, vars.pl_y,
			vars.pl_x, vars.sq_y + 1) - PLAYER_RAD > EPS)
	{
		return (1);
	}
	return (0);
}
