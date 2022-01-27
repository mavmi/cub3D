/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:37:48 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/27 11:43:52 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

// Get distance between {x1, y1} and {x2, y2}
double	paint_get_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

// Get module of number
double	paint_get_module(double num)
{
	return (sqrt(pow(num, 2)));
}

// Convert t_color to int
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

void	paint_put_pixel(t_painting *painting, int x, int y, t_color color)
{
	int	pos;

	if (!painting)
		return ;
	pos = y * painting->size_line + x * (painting->bits_per_pixel / 8);
	*(int *)(painting->data_addr + pos) = paint_get_color(color);
}
