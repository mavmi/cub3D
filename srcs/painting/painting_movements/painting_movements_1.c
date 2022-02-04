/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_movements_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:36:15 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/04 16:45:04 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

static t_movements	paint_movements_get_vars(t_painting *p, t_movement movement)
{
	t_movements	vars;

	vars.vector = paint_ray_get_orient_vector(ORIENT_SOUTH);
	vars.vector->end->y *= PL_STEP;
	if (!vars.vector)
		return (vars);
	if (movement == MOVE_FORWARD)
		vars.angle = p->map->player->angle;
	else if (movement == MOVE_BACK)
		vars.angle = paint_room_increase_angle(p->map->player->angle, 180);
	else if (movement == MOVE_LEFT)
		vars.angle = paint_room_increase_angle(p->map->player->angle, 270);
	else if (movement == MOVE_RIGHT)
		vars.angle = paint_room_increase_angle(p->map->player->angle, 90);
	vars.ray_of_view = paint_ray_get_ray_of_view(p, vars.angle);
	if (!vars.ray_of_view)
	{
		geom_destroy_vector(vars.vector);
		return (vars);
	}
	vars.len = geom_vector_get_module(vars.ray_of_view->ray);
	return (vars);
}

void	paint_movements_move(t_painting *painting, t_movement movement)
{
	t_movements	vars;

	if (!vars.vector || !vars.ray_of_view)
		return ;
	vars = paint_movements_get_vars(painting, movement);
	if (vars.len > PL_STEP + 0.25)
	{
		vars.cos_ = cos(utils_degree_to_rad(vars.angle));
		vars.sin_ = sin(utils_degree_to_rad(vars.angle));
		vars.x = (vars.vector->end->x * vars.cos_
				- vars.vector->end->y * vars.sin_) * PL_STEP;
		vars.y = (vars.vector->end->y * vars.cos_
				+ vars.vector->end->x * vars.sin_) * PL_STEP;
		vars.vector->end->x = vars.x;
		vars.vector->end->y = vars.y;
		geom_move_vector(vars.vector, painting->map->player->pos);
		painting->map->player->pos->x = vars.vector->end->x;
		painting->map->player->pos->y = vars.vector->end->y;
	}
	geom_destroy_vector(vars.vector);
	paint_ray_destroy_ray_of_view(vars.ray_of_view);
}
