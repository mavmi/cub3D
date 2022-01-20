/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:37:48 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/20 17:28:33 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

double	paint_get_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

double	paint_get_module(double num)
{
	return (sqrt(pow(num, 2)));
}

int	paint_get_color(t_color color)
{
	if (color == COLOR_WALL)
		return (0xFFFFFF);
	if (color == COLOR_GRID)
		return (0xFF0000);
	if (color == COLOR_PLAYER)
		return (0xFFFF00);
	if (color == COLOR_RAY)
		return (0x0000FF);
	return (0x000000);
}
