/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:00:43 by msalena           #+#    #+#             */
/*   Updated: 2022/03/19 15:11:49 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

static int	first_if(t_ray_vars *vars, char *type)
{
	if (vars->painting->cl_door_fl == 2)
	{
		(*type) = MAP_SQ_OP_DOOR;
		vars->painting->cl_door_fl = 0;
		return (0);
	}
	return (2);
}

static int	second_if(t_ray_vars *vars, char *type)
{
	if (vars->painting->cl_door_fl == 2)
	{
		(*type) = MAP_SQ_CL_DOOR;
		vars->painting->cl_door_fl = 0;
		return (2);
	}
	return (3);
}

/*
	Check if {x, y} point belongs to a wall
*/
int	paint_ray_is_wall_or_door(t_ray_vars *vars, double x, double y)
{
	char	*type;

	paint_ray_decrease_coord(vars, &x, &y);
	type = &(vars->painting->map->lines[(int)y]->line[(int)x]->type);
	if (vars->painting->map->lines[(int)y]->line[(int)x]->type == MAP_SQ_WALL)
		return (1);
	else if (*type == MAP_SQ_CL_DOOR)
	{
		return (first_if(vars, type));
	}
	else if (*type == MAP_SQ_OP_DOOR
		&& vars->painting->cl_door_fl > 0)
	{
		return (second_if(vars, type));
	}
	else if (*type == MAP_SQ_GIF)
		return (4);
	return (0);
}
