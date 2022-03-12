/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_movements_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:36:15 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/12 17:44:55 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

/*
	Get t_move_vars to make some calculations
*/
static t_move_vars	paint_movements_get_vars(t_painting *p, t_movement movement)
{
	t_move_vars	vars;

	vars.vector = paint_ray_get_orient_vector(ORIENT_SOUTH);
	vars.vector->end->y *= PL_STEP;
	if (!vars.vector)
		return (vars);
	if (movement == MOVE_FORWARD || movement == MOVE_DOOR)
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

/*
	Move player if it's far away from wall
*/
void	paint_movements_move(t_painting *painting, t_movement movement)
{
	t_move_vars	vars;

	if (!vars.vector || !vars.ray_of_view)
		return ;
	vars = paint_movements_get_vars(painting, movement);
	if (movement == MOVE_DOOR && (vars.ray_of_view->orient == ORIENT_CL_DOOR
			|| vars.ray_of_view->orient == ORIENT_OP_DOOR)
			&& vars.len > PL_STEP + 0.2 && vars.len < PL_STEP + 1)
	{
painting->cl_door_fl = 2;
	}
	else if (movement != MOVE_DOOR && vars.len > PL_STEP + 0.2)
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
	else
		painting->cl_door_fl = 0;
	geom_destroy_vector(vars.vector);
	paint_ray_destroy_ray_of_view(vars.ray_of_view);
}
