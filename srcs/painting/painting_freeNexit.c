/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_freeNexit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:17:41 by msalena           #+#    #+#             */
/*   Updated: 2022/03/19 14:51:42 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

/*
	It must be obvious tho
*/
void	paint_ray_destroy_ray_of_view(t_ray_of_view *ray_of_view)
{
	if (!ray_of_view)
		return ;
	geom_destroy_vector(ray_of_view->ray);
	free(ray_of_view);
}

static void	free_txtrs(t_painting *painting)
{
	if (painting->t_north)
	{
		mlx_destroy_image(painting->mlx, painting->t_north->drawable.img);
		free(painting->t_north);
	}
	if (painting->t_east)
	{
		mlx_destroy_image(painting->mlx, painting->t_east->drawable.img);
		free(painting->t_east);
	}
	if (painting->t_south)
	{
		mlx_destroy_image(painting->mlx, painting->t_south->drawable.img);
		free(painting->t_south);
	}
	if (painting->t_west)
	{
		mlx_destroy_image(painting->mlx, painting->t_west->drawable.img);
		free(painting->t_west);
	}
	if (painting->t_door)
	{
		mlx_destroy_image(painting->mlx, painting->t_door->drawable.img);
		free(painting->t_door);
	}
}

/*
	Free all and exit
*/
void	paint_exit(t_painting *painting)
{
	int	i;

	i = 0;
	if (painting)
	{
		pars_destroy_map(painting->map);
		painting->map = NULL;
		mlx_destroy_image(painting->mlx, painting->minimap.img);
		mlx_destroy_image(painting->mlx, painting->room.img);
		free_txtrs(painting);
		while (i < 10)
		{
			if (painting->t_gif[i])
			{
				mlx_destroy_image(painting->mlx,
					painting->t_gif[i]->drawable.img);
				free(painting->t_gif[i]);
			}
			i++;
		}
		free(painting->t_gif);
		mlx_destroy_window(painting->mlx, painting->win);
		free(painting);
	}
	exit(0);
}
