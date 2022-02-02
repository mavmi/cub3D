/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_room_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:21:19 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 13:22:02 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/painting.h"

double	paint_room_decrease_angle(double angle, double delta)
{
	if (angle > delta)
		return (angle - delta);
	return (360.0 - (sqrt(pow(angle - delta, 2))));
}

double	paint_room_increase_angle(double angle, double delta)
{
	if (angle + delta < 360.0)
		return (angle + delta);
	return (delta - (360.0 - angle));
}

t_color	paint_room_get_color_from_orien(t_orient orient)
{
	if (orient == ORIENT_NORTH)
		return (COLOR_NORTH);
	if (orient == ORIENT_SOUTH)
		return (COLOR_SOUTH);
	if (orient == ORIENT_EAST)
		return (COLOR_EAST);
	if (orient == ORIENT_WEST)
		return (COLOR_WEST);
	return (COLOR_GREEN);
}
