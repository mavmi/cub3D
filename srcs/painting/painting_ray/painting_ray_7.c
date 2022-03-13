/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:00:21 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/13 19:26:46 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

/*
	Set wall's orientation when vector hits it
*/
void	paint_ray_set_ray_orient(t_ray_vars *vars)
{
	if (vars->ray_of_view->orient == ORIENT_CL_DOOR)
		return ;
	else if (vars->octet == 1 || vars->octet == 7)
		vars->ray_of_view->orient = ORIENT_NORTH;
	else if (vars->octet == 6 || vars->octet == 8)
		vars->ray_of_view->orient = ORIENT_WEST;
	else if (vars->octet == 2 || vars->octet == 4)
		vars->ray_of_view->orient = ORIENT_EAST;
	else if (vars->octet == 3 || vars->octet == 5)
		vars->ray_of_view->orient = ORIENT_SOUTH;
}

int	paint_ray_decrease_coord_assignment(t_decrease *decr)
{
	if (decr->vars->painting->map
		->lines[(int)decr->tmp_y]->line[(int)decr->tmp_x]->type == MAP_SQ_WALL)
	{
		*decr->x = decr->tmp_x;
		*decr->y = decr->tmp_y;
		return (1);
	}
	return (0);
}

/*
	Get octet from quarter and angleX
*/
int	paint_ray_get_octet(int quarter, int part)
{
	return (2 * quarter - 1 + part);
}

/*
	Check if {x, y} point belongs to a wall
*/
int	paint_ray_is_wall_or_door(t_ray_vars *vars, double x, double y)
{
	paint_ray_decrease_coord(vars, &x, &y);
	if (vars->painting->map->lines[(int)y]->line[(int)x]->type == MAP_SQ_WALL)
		return (1);
	else if (vars->painting->map->lines[(int)y]->line[(int)x]->type == MAP_SQ_CL_DOOR)
	{
		if (vars->painting->cl_door_fl == 2)
		{
			vars->painting->map->lines[(int)y]->line[(int)x]->type = MAP_SQ_OP_DOOR;
			vars->painting->cl_door_fl = 0;
			return (0);
		}
		return (2);
	}
	else if (vars->painting->map->lines[(int)y]->line[(int)x]->type == MAP_SQ_OP_DOOR
				&& vars->painting->cl_door_fl > 0)
	{
		if (vars->painting->cl_door_fl == 2)
		{
			vars->painting->map->lines[(int)y]->line[(int)x]->type = MAP_SQ_CL_DOOR;
			vars->painting->cl_door_fl = 0;
			return (2);
		}
		return (3);
	}
	else if (vars->painting->map->lines[(int)y]->line[(int)x]->type == MAP_SQ_GIF)
		return (4);
	return (0);
}

/*
	Update t_ray_getter's [delta], [corner_angle] and [octet].
	Return 0 if everything is fine, 1 otherwise
*/
int	paint_ray_get_delta_angle_octet(t_ray_vars *vars)
{
	t_vector	*corner_v;

	if (!vars)
		return (1);
	corner_v = paint_ray_get_corner_vector(vars->ray_of_view->ray->end,
			vars->ray_info->quarter);
	if (!corner_v)
		return (1);
	vars->corner_angle = geom_get_angle(vars->ray_info->orient_vert,
			corner_v);
	if (vars->corner_angle > 90.0)
		vars->corner_angle -= 90.0;
	if (vars->ray_info->quarter_angle <= vars->corner_angle)
		vars->octet = paint_ray_get_octet(vars->ray_info->quarter, 0);
	else
		vars->octet = paint_ray_get_octet(vars->ray_info->quarter, 1);
	if (vars->octet % 2 != 0)
		vars->delta = sqrt(pow(corner_v->begin->y - corner_v->end->y, 2))
			* tan(utils_degree_to_rad(vars->ray_info->quarter_angle));
	else
		vars->delta = sqrt(pow(corner_v->begin->x - corner_v->end->x, 2))
			* tan(utils_degree_to_rad(90 - vars->ray_info->quarter_angle));
	geom_destroy_vector(corner_v);
	return (0);
}
