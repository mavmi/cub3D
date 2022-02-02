/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_minimap_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:36:47 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 16:39:58 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

// Vector's printer.
// It draws vector
static void	paint_minimap_vector_printer(t_painting *painting,
			t_vector *vector, t_color color)
{
	double	dx;
	double	dy;
	double	x;
	double	y;
	int		pixels;

	if (!painting || !vector)
		return ;
	dx = (int)((vector->end->x - vector->begin->x) * PIXEL_SIZE);
	dy = (int)((vector->end->y - vector->begin->y) * PIXEL_SIZE);
	pixels = sqrt(pow(dx, 2) + pow(dy, 2));
	dx /= pixels;
	dy /= pixels;
	x = vector->begin->x * PIXEL_SIZE;
	y = vector->begin->y * PIXEL_SIZE;
	while (pixels--)
	{
		if ((int)x % PIXEL_SIZE == 0 || (int)y % PIXEL_SIZE == 0)
			paint_put_pixel(painting, x, y, COLOR_GRID);
		else
			paint_put_pixel(painting, x, y, color);
		x += dx;
		y += dy;
	}
}

// Draw vector in canvas
void	paint_minimap_draw_vector(t_painting *painting, t_vector *vector)
{
	if (!painting || !vector)
		return ;
	paint_minimap_vector_printer(painting, vector, COLOR_RAY);
}

// Delete vector from canvas
void	paint_minimap_erase_vector(t_painting *painting, t_vector *vector)
{
	if (!painting || !vector)
		return ;
	paint_minimap_vector_printer(painting, vector, COLOR_FIELD);
}
