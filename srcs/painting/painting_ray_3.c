/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:01:38 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/18 20:34:53 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

void	paint_print_ray(t_painting *painting)
{
	t_ray	*ray;

	if (!painting)
		return ;
	ray = paint_get_ray_info(painting);
	if (!ray)
		return ;
	printf("\t========================\n");
	printf("abs angle: %d\n", painting->map->player->angle);
	printf("quarter: %d\n", ray->quarter);
	printf("quarter angle: %d\n", ray->quarter_angle);
	paint_destroy_ray_info(ray);
}
