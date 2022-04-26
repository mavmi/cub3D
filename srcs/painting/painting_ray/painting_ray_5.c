/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:58:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/08 17:03:28 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

static void	paint_ray_append_vector_4(t_ray_vars *vars)
{
	if (vars->octet == 7)
	{
		vars->ray_of_view->ray->end->x -= vars->delta;
		if (utils_is_double_integer(vars->ray_of_view->ray->end->y))
			vars->ray_of_view->ray->end->y -= 1.0;
		else
			vars->ray_of_view->ray->end->y
				= utils_round_double_down(vars->ray_of_view->ray->end->y);
	}
	else if (vars->octet == 8)
	{	
		if (utils_is_double_integer(vars->ray_of_view->ray->end->x))
			vars->ray_of_view->ray->end->x -= 1.0;
		else
			vars->ray_of_view->ray->end->x
				= utils_round_double_down(vars->ray_of_view->ray->end->x);
		vars->ray_of_view->ray->end->y -= vars->delta;
	}
}

static void	paint_ray_append_vector_3(t_ray_vars *vars)
{
	if (vars->octet == 5)
	{
		vars->ray_of_view->ray->end->x -= vars->delta;
		if (utils_is_double_integer(vars->ray_of_view->ray->end->y))
			vars->ray_of_view->ray->end->y += 1.0;
		else
			vars->ray_of_view->ray->end->y
				= utils_round_double_up(vars->ray_of_view->ray->end->y);
	}
	else if (vars->octet == 6)
	{
		if (utils_is_double_integer(vars->ray_of_view->ray->end->x))
			vars->ray_of_view->ray->end->x -= 1.0;
		else
			vars->ray_of_view->ray->end->x
				= utils_round_double_down(vars->ray_of_view->ray->end->x);
		vars->ray_of_view->ray->end->y += vars->delta;
	}
}

static void	paint_ray_append_vector_2(t_ray_vars *vars)
{
	if (vars->octet == 3)
	{
		vars->ray_of_view->ray->end->x += vars->delta;
		if (utils_is_double_integer(vars->ray_of_view->ray->end->y))
			vars->ray_of_view->ray->end->y += 1.0;
		else
			vars->ray_of_view->ray->end->y
				= utils_round_double_up(vars->ray_of_view->ray->end->y);
	}
	else if (vars->octet == 4)
	{
		if (utils_is_double_integer(vars->ray_of_view->ray->end->x))
			vars->ray_of_view->ray->end->x += 1.0;
		else
			vars->ray_of_view->ray->end->x
				= utils_round_double_up(vars->ray_of_view->ray->end->x);
		vars->ray_of_view->ray->end->y += vars->delta;
	}
}

static void	paint_ray_append_vector_1(t_ray_vars *vars)
{
	if (vars->octet == 1)
	{
		vars->ray_of_view->ray->end->x += vars->delta;
		if (utils_is_double_integer(vars->ray_of_view->ray->end->y))
			vars->ray_of_view->ray->end->y -= 1.0;
		else
			vars->ray_of_view->ray->end->y
				= utils_round_double_down(vars->ray_of_view->ray->end->y);
	}
	else if (vars->octet == 2)
	{			
		if (utils_is_double_integer(vars->ray_of_view->ray->end->x))
			vars->ray_of_view->ray->end->x += 1.0;
		else
			vars->ray_of_view->ray->end->x
				= utils_round_double_up(vars->ray_of_view->ray->end->x);
		vars->ray_of_view->ray->end->y -= vars->delta;
	}
}

/*
	Update [end] of player's vector of view
*/
int	paint_ray_append_vector(t_ray_vars *vars)
{
	if (!vars)
		return (1);
	if (vars->ray_info->quarter == 1)
		paint_ray_append_vector_1(vars);
	else if (vars->ray_info->quarter == 2)
		paint_ray_append_vector_2(vars);
	else if (vars->ray_info->quarter == 3)
		paint_ray_append_vector_3(vars);
	else if (vars->ray_info->quarter == 4)
		paint_ray_append_vector_4(vars);
	return (0);
}
