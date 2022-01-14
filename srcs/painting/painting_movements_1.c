/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_movements_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:36:15 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/14 20:09:16 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

void	paint_move_left(t_painting *painting)
{
	if (paint_is_move_left(painting))
	{
		painting->map->player->pos->x -= STEP;
	}
}

void	paint_move_right(t_painting *painting)
{
	if (paint_is_move_right(painting))
	{
		painting->map->player->pos->x += STEP;
	}
}

void	paint_move_up(t_painting *painting)
{
	if (paint_is_move_up(painting))
	{
		painting->map->player->pos->y -= STEP;
	}
}

void	paint_move_down(t_painting *painting)
{
	if (paint_is_move_down(painting))
	{
		painting->map->player->pos->y += STEP;
	}
}
