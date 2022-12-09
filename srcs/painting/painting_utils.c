/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:37:48 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/13 20:30:47 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

/*
	Get distance between {x1, y1} and {x2, y2}
*/
double	paint_get_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

/*
	Make number absolute
*/
double	paint_get_module(double num)
{
	return (sqrt(pow(num, 2)));
}

/*
	Convert t_color to int
*/
int	paint_get_color(t_color color)
{
	if (color == COLOR_WALL)
		return (0xFFFFFF);
	if (color == COLOR_DOOR)
		return (0xDEB887);
	if (color == COLOR_GIF)
		return (0xADD8E6);
	if (color == COLOR_GRID)
		return (0xFF0000);
	if (color == COLOR_PLAYER)
		return (0xFFFF00);
	if (color == COLOR_FIELD)
		return (0x808080);
	if (color == COLOR_TRANSPARENT)
		return (0xFF000000);
	return (0x000000);
}

void	paint_put_color(t_drawable *drawable, int x, int y, t_color color)
{
	int	pos;

	if (!drawable)
		return ;
	pos = y * drawable->size_line + x * (drawable->bits_per_pixel / 8);
	*(int *)(drawable->img_addr + pos) = paint_get_color(color);
}

void	paint_put_pixel(t_drawable *drawable, int x, int y, int pixel)
{
	int	pos;

	if (!drawable)
		return ;
	pos = y * drawable->size_line + x * (drawable->bits_per_pixel / 8);
	*(int *)(drawable->img_addr + pos) = pixel;
}
