/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:59:52 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 13:19:19 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

static void	paint_decrease_coord_7_8(t_decrease *decr)
{
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_WEST;
		return ;
	}
	decr->tmp_x = *decr->x;
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_NORTH;
		return ;
	}
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_NORTH;
		return ;
	}
}

static void	paint_decrease_coord_5_6(t_decrease *decr)
{
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_WEST;
		return ;
	}
	decr->tmp_x = *decr->x;
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_SOUTH;
		return ;
	}
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_SOUTH;
		return ;
	}
}

static void	paint_decrease_coord_3_4(t_decrease *decr)
{
	decr->tmp_x = *decr->x;
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_EAST;
		return ;
	}
	decr->tmp_x = *decr->x;
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_SOUTH;
		return ;
	}
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_SOUTH;
		return ;
	}
}

static void	paint_decrease_coord_1_2(t_decrease *decr)
{
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_NORTH;
		return ;
	}
	decr->tmp_x = *decr->x;
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_NORTH;
		return ;
	}
	decr->tmp_x = *decr->x;
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
	{
		decr->vars->ray_of_view->orient = ORIENT_EAST;
		return ;
	}
}

void	paint_decrease_coord(t_ray_getter *vars, double *x, double *y)
{
	t_decrease	decr;

	decr.x = x;
	decr.y = y;
	decr.delta = 0.1;
	decr.vars = vars;
	if (utils_is_double_integer(*x) && utils_is_double_integer(*y))
	{
		if (vars->octet == 7 || vars->octet == 8)
			paint_decrease_coord_7_8(&decr);
		if (vars->octet == 5 || vars->octet == 6)
			paint_decrease_coord_5_6(&decr);
		if (vars->octet == 3 || vars->octet == 4)
			paint_decrease_coord_3_4(&decr);
		if (vars->octet == 1 || vars->octet == 2)
			paint_decrease_coord_1_2(&decr);
	}
	else if (vars->octet == 1 || vars->octet == 7)
		*y -= decr.delta;
	else if (vars->octet == 6 || vars->octet == 8)
		*x -= decr.delta;
	paint_set_ray_orient(vars);
}
