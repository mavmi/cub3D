/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_movements_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <username@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:36:15 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/26 00:40:21 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

// All these functions just change position of player
//
// Just to be sure: player's position doesn't depend on
// PIXEL_SIZE. It's an absolute double value

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
