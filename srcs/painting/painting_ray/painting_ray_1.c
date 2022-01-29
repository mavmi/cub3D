/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:21:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/29 18:13:55 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

// All these functions are about decreasing ray vector's coordinates
// at the end of cycle iteration

static int	paint_decrease_coord_assignment(t_decrease *decr)
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

static void	paint_decrease_coord_7_8(t_decrease *decr)
{
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
		return ;
	decr->tmp_x = *decr->x;
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
		return ;
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
		return ;
}

static void	paint_decrease_coord_5_6(t_decrease *decr)
{
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
		return ;
	decr->tmp_x = *decr->x;
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
		return ;
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
		return ;
}

static void	paint_decrease_coord_3_4(t_decrease *decr)
{
	decr->tmp_x = *decr->x;
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
		return ;
	decr->tmp_x = *decr->x;
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
		return ;
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
		return ;
}

static void	paint_decrease_coord_1_2(t_decrease *decr)
{
	decr->tmp_x = utils_round_double_down(*decr->x - decr->delta);
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
		return ;
	decr->tmp_x = *decr->x;
	decr->tmp_y = utils_round_double_down(*decr->y - decr->delta);
	if (paint_decrease_coord_assignment(decr))
		return ;
	decr->tmp_x = *decr->x;
	decr->tmp_y = *decr->y;
	if (paint_decrease_coord_assignment(decr))
		return ;
}

static void	paint_decrease_coord(t_ray_getter *vars, double *x, double *y)
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
}

// Get quarter depending on [quarter], [quarter_angle] and [corner_angle]
static int	paint_get_octet(int quarter, int part)
{
	return (2 * quarter - 1 + part);
}

static int	paint_is_wall(t_ray_getter *vars, double x, double y)
{
	paint_decrease_coord(vars, &x, &y);
	if (vars->painting->map->lines[(int)y]->line[(int)x]->type == MAP_SQ_WALL)
		return (1);
	return (0);
}

// All these functions update [end] of player's vector of view
// depending on it's octet

static void	paint_append_vector_4(t_ray_getter *vars)
{
	if (vars->octet == 7)
	{
		vars->ray_vector->end->x -= vars->delta;
		if (utils_is_double_integer(vars->ray_vector->end->y))
			vars->ray_vector->end->y -= 1.0;
		else
			vars->ray_vector->end->y
				= utils_round_double_down(vars->ray_vector->end->y);
	}
	else if (vars->octet == 8)
	{	
		if (utils_is_double_integer(vars->ray_vector->end->x))
			vars->ray_vector->end->x -= 1.0;
		else
			vars->ray_vector->end->x
				= utils_round_double_down(vars->ray_vector->end->x);
		vars->ray_vector->end->y -= vars->delta;
	}
}

static void	paint_append_vector_3(t_ray_getter *vars)
{
	if (vars->octet == 5)
	{
		vars->ray_vector->end->x -= vars->delta;
		if (utils_is_double_integer(vars->ray_vector->end->y))
			vars->ray_vector->end->y += 1.0;
		else
			vars->ray_vector->end->y
				= utils_round_double_up(vars->ray_vector->end->y);
	}
	else if (vars->octet == 6)
	{
		if (utils_is_double_integer(vars->ray_vector->end->x))
			vars->ray_vector->end->x -= 1.0;
		else
			vars->ray_vector->end->x
				= utils_round_double_down(vars->ray_vector->end->x);
		vars->ray_vector->end->y += vars->delta;
	}
}

static void	paint_append_vector_2(t_ray_getter *vars)
{
	if (vars->octet == 3)
	{
		vars->ray_vector->end->x += vars->delta;
		if (utils_is_double_integer(vars->ray_vector->end->y))
			vars->ray_vector->end->y += 1.0;
		else
			vars->ray_vector->end->y
				= utils_round_double_up(vars->ray_vector->end->y);
	}
	else if (vars->octet == 4)
	{
		if (utils_is_double_integer(vars->ray_vector->end->x))
			vars->ray_vector->end->x += 1.0;
		else
			vars->ray_vector->end->x
				= utils_round_double_up(vars->ray_vector->end->x);
		vars->ray_vector->end->y += vars->delta;
	}
}

static void	paint_append_vector_1(t_ray_getter *vars)
{
	if (vars->octet == 1)
	{
		vars->ray_vector->end->x += vars->delta;
		if (utils_is_double_integer(vars->ray_vector->end->y))
			vars->ray_vector->end->y -= 1.0;
		else
			vars->ray_vector->end->y
				= utils_round_double_down(vars->ray_vector->end->y);
	}
	else if (vars->octet == 2)
	{			
		if (utils_is_double_integer(vars->ray_vector->end->x))
			vars->ray_vector->end->x += 1.0;
		else
			vars->ray_vector->end->x
				= utils_round_double_up(vars->ray_vector->end->x);
		vars->ray_vector->end->y -= vars->delta;
	}
}

// Update [end] of player's vector of view
static int	paint_append_vector(t_ray_getter *vars)
{
	if (!vars)
		return (1);
	if (vars->ray_info->quarter == 1)
		paint_append_vector_1(vars);
	else if (vars->ray_info->quarter == 2)
		paint_append_vector_2(vars);
	else if (vars->ray_info->quarter == 3)
		paint_append_vector_3(vars);
	else if (vars->ray_info->quarter == 4)
		paint_append_vector_4(vars);
	return (0);
}

// Update t_ray_getter's [delta], [corner_angle] and [octet].
// Return 0 if everything is fine, 1 otherwise
static int	paint_get_delta_angle_octet(t_ray_getter *vars)
{
	t_vector	*corner_v;

	if (!vars)
		return (1);
	corner_v = paint_get_corner_vector(vars->ray_vector->end,
			vars->ray_info->quarter);
	if (!corner_v)
		return (1);
	vars->corner_angle = geom_get_angle(vars->ray_info->orient_vert,
			corner_v);
	if (vars->corner_angle > 90.0)
		vars->corner_angle -= 90.0;
	if (vars->ray_info->quarter_angle <= vars->corner_angle)
		vars->octet = paint_get_octet(vars->ray_info->quarter, 0);
	else
		vars->octet = paint_get_octet(vars->ray_info->quarter, 1);
	if (vars->octet % 2 != 0)
		vars->delta = sqrt(pow(corner_v->begin->y - corner_v->end->y, 2))
			* tan(utils_degree_to_rad(vars->ray_info->quarter_angle));
	else
		vars->delta = sqrt(pow(corner_v->begin->x - corner_v->end->x, 2))
			* tan(utils_degree_to_rad(90 - vars->ray_info->quarter_angle));
	geom_destroy_vector(corner_v);
	return (0);
}

// Just initialization of player's vector of view.
// It's begin and end point are equal to players position.
// May return NULL
static t_vector	*paint_init_ray_vector(t_painting *painting)
{
	t_point		*begin;
	t_point		*end;
	t_vector	*vector;

	if (!painting)
		return (NULL);
	begin = geom_init_point(painting->map->player->pos->x,
			painting->map->player->pos->y);
	end = geom_init_point(painting->map->player->pos->x,
			painting->map->player->pos->y);
	if (!begin || !end)
	{
		geom_destroy_point(begin);
		geom_destroy_point(end);
		return (NULL);
	}
	vector = geom_init_vector(begin, end);
	if (vector)
		return (vector);
	geom_destroy_point(begin);
	geom_destroy_point(end);
	return (NULL);
}

// Create player's vector of view
static t_vector	*paint_get_ray_vector(t_painting *painting, t_ray *ray_info)
{	
	t_ray_getter	vars;

	if (!painting || !ray_info)
		return (NULL);
	vars.painting = painting;
	vars.ray_info = ray_info;
	vars.ray_vector = paint_init_ray_vector(painting);
	if (!vars.ray_vector)
		return (NULL);
	while (1)
	{
		if (paint_get_delta_angle_octet(&vars) || paint_append_vector(&vars))
		{
			geom_destroy_vector(vars.ray_vector);
			return (NULL);
		}
		if (paint_is_wall(&vars, vars.ray_vector->end->x,
				vars.ray_vector->end->y))
			break ;
		paint_decrease_coord(&vars, &vars.ray_vector->end->x,
			&vars.ray_vector->end->y);
	}
	return (vars.ray_vector);
}

// Welcome to my doom
//
// It gets all information about map,
// calculate orientation of player's vector of view
// and draw it
t_vector	*paint_get_ray_of_view(t_painting *painting, double angle)
{
	t_ray			*ray_info;
	t_vector		*ray_vector;

	if (!painting)
		return (NULL);
	ray_info = paint_get_ray_info(painting->map->player->angle);
	if (!ray_info)
		return (NULL);
	ray_vector = paint_get_ray_vector(painting, ray_info);
	paint_destroy_ray_info(ray_info);
	if (ray_vector)
		return (ray_vector);
	return (NULL);
}
