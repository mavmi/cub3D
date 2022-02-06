/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:21:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/06 20:19:21 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

void	paint_ray_destroy_ray_of_view(t_ray_of_view *ray_of_view)
{
	if (!ray_of_view)
		return ;
	geom_destroy_vector(ray_of_view->ray);
	free(ray_of_view);
}

// Just initialization of player's vector of view.
// It's begin and end point are equal to players position.
// May return NULL
static t_vector	*paint_ray_init_ray_vector(t_painting *painting)
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

static t_ray_of_view	*paint_ray_init_ray_of_view(t_painting *painting)
{
	t_ray_of_view	*ray_of_view;

	if (!painting)
		return (NULL);
	ray_of_view = (t_ray_of_view *)malloc(sizeof(t_ray_of_view));
	if (!ray_of_view)
		return (NULL);
	ray_of_view->ray = paint_ray_init_ray_vector(painting);
	if (ray_of_view->ray)
		return (ray_of_view);
	paint_ray_destroy_ray_of_view(ray_of_view);
	return (NULL);
}

// Create player's vector of view
static t_ray_of_view	*paint_ray_get_ray_vector(t_painting *painting,
							t_ray *ray_info)
{	
	t_ray_vars	vars;

	if (!painting || !ray_info)
		return (NULL);
	vars.painting = painting;
	vars.ray_info = ray_info;
	vars.ray_of_view = paint_ray_init_ray_of_view(painting);
	if (!vars.ray_of_view)
		return (NULL);
	while (1)
	{
		if (paint_ray_get_delta_angle_octet(&vars)
			|| paint_ray_append_vector(&vars))
		{
			paint_ray_destroy_ray_of_view(vars.ray_of_view);
			return (NULL);
		}
		if (paint_ray_is_wall(&vars, vars.ray_of_view->ray->end->x,
				vars.ray_of_view->ray->end->y))
			return (vars.ray_of_view);
		paint_ray_decrease_coord(&vars, &vars.ray_of_view->ray->end->x,
			&vars.ray_of_view->ray->end->y);
	}
}

// Welcome to my doom
//
// It gets all information about map,
// calculate orientation of player's vector of view
// and draw it
t_ray_of_view	*paint_ray_get_ray_of_view(t_painting *painting, double angle)
{
	t_ray			*ray_info;
	t_ray_of_view	*ray_of_view;

	if (!painting)
		return (NULL);
	ray_info = paint_ray_get_ray_info(angle);
	if (!ray_info)
		return (NULL);
	ray_of_view = paint_ray_get_ray_vector(painting, ray_info);
	paint_ray_destroy_ray_info(ray_info);
	if (ray_of_view)
		return (ray_of_view);
	return (NULL);
}
