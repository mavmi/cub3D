/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:21:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/26 15:29:43 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

// Get quarter depending on [quarter], [quarter_angle] and [corner_angle]
static int	paint_get_octet(int quarter, int part)
{
	return (2 * quarter - 1 + part);
}

static void	paint_decrease_coord(int *x, int *y, int octet)
{
	if (octet == 1 || octet == 7)
		(*y)--;
	if (octet == 6 || octet == 8)
		(*x)--;
}

// Check if {pixel_x, pixel_y} pixel belongs to wall.
// Return 1 if it does, 0 otherwise
static int	paint_is_wall(t_painting *painting, int octet,
					int pixel_x, int pixel_y)
{	
	paint_decrease_coord(&pixel_x, &pixel_y, octet);
	pixel_x -= pixel_x % PIXEL_SIZE;
	pixel_y -= pixel_y % PIXEL_SIZE;
	pixel_x /= PIXEL_SIZE;
	pixel_y /= PIXEL_SIZE;
	if (painting->map->lines[pixel_y]->line[pixel_x]->type == WALL)
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
		if (vars->ray_vector->end->y % PIXEL_SIZE)
			vars->ray_vector->end->y = vars->ray_vector->end->y
				- vars->ray_vector->end->y % PIXEL_SIZE;
		else
			vars->ray_vector->end->y = vars->ray_vector->end->y - PIXEL_SIZE;
	}
	else if (vars->octet == 8)
	{
		if (vars->ray_vector->end->x % PIXEL_SIZE)
			vars->ray_vector->end->x = vars->ray_vector->end->x
				- vars->ray_vector->end->x % PIXEL_SIZE;
		else
			vars->ray_vector->end->x = vars->ray_vector->end->x - PIXEL_SIZE;
		vars->ray_vector->end->y -= vars->delta;
	}
}

static void	paint_append_vector_3(t_ray_getter *vars)
{
	if (vars->octet == 5)
	{
		vars->ray_vector->end->x -= vars->delta;
		if (vars->ray_vector->end->y % PIXEL_SIZE)
			vars->ray_vector->end->y = vars->ray_vector->end->y
				- vars->ray_vector->end->y % PIXEL_SIZE + PIXEL_SIZE;
		else
			vars->ray_vector->end->y += PIXEL_SIZE;
	}
	else if (vars->octet == 6)
	{
		if (vars->ray_vector->end->x % PIXEL_SIZE)
			vars->ray_vector->end->x = vars->ray_vector->end->x
				- vars->ray_vector->end->x % PIXEL_SIZE;
		else
			vars->ray_vector->end->x = vars->ray_vector->end->x - PIXEL_SIZE;
		vars->ray_vector->end->y += vars->delta;
	}
}

static void	paint_append_vector_2(t_ray_getter *vars)
{
	if (vars->octet == 3)
	{
		vars->ray_vector->end->x += vars->delta;
		if (vars->ray_vector->end->y % PIXEL_SIZE)
			vars->ray_vector->end->y = vars->ray_vector->end->y
				- vars->ray_vector->end->y % PIXEL_SIZE + PIXEL_SIZE;
		else
			vars->ray_vector->end->y += PIXEL_SIZE;
	}
	else if (vars->octet == 4)
	{
		if (vars->ray_vector->end->x % PIXEL_SIZE)
			vars->ray_vector->end->x = vars->ray_vector->end->x
				- vars->ray_vector->end->x % PIXEL_SIZE + PIXEL_SIZE;
		else
			vars->ray_vector->end->x = vars->ray_vector->end->x + PIXEL_SIZE;
		vars->ray_vector->end->y += vars->delta;
	}
}

static void	paint_append_vector_1(t_ray_getter *vars)
{
	if (vars->octet == 1)
	{
		vars->ray_vector->end->x += vars->delta;
		if (vars->ray_vector->end->y % PIXEL_SIZE)
			vars->ray_vector->end->y = vars->ray_vector->end->y
				- vars->ray_vector->end->y % PIXEL_SIZE;
		else
			vars->ray_vector->end->y = vars->ray_vector->end->y - PIXEL_SIZE;
	}
	else if (vars->octet == 2)
	{
		if (vars->ray_vector->end->x % PIXEL_SIZE)
			vars->ray_vector->end->x = vars->ray_vector->end->x
				- vars->ray_vector->end->x % PIXEL_SIZE + PIXEL_SIZE;
		else
			vars->ray_vector->end->x += PIXEL_SIZE;
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
	begin = geom_init_point(painting->map->player->pos->x * PIXEL_SIZE,
			painting->map->player->pos->y * PIXEL_SIZE, 0);
	end = geom_init_point(painting->map->player->pos->x * PIXEL_SIZE,
			painting->map->player->pos->y * PIXEL_SIZE, 0);
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
		if (paint_is_wall(painting, vars.octet, vars.ray_vector->end->x,
				vars.ray_vector->end->y))
			break ;
		paint_decrease_coord(&vars.ray_vector->end->x,
			&vars.ray_vector->end->y, vars.octet);
	}	
	return (vars.ray_vector);
}

// Welcome to my doom
//
// It gets all information about map,
// calculate orientation of player's vector of view
// and draw it
t_vector	*paint_get_ray_of_view(t_painting *painting)
{
	t_ray			*ray_info;
	t_vector		*ray_vector;

	if (!painting)
		return (NULL);
	ray_info = paint_get_ray_info(painting);
	if (!ray_info)
		return (NULL);
	ray_vector = paint_get_ray_vector(painting, ray_info);
	paint_destroy_ray_info(ray_info);
	if (ray_vector)
		return (ray_vector);
	return (NULL);
}
