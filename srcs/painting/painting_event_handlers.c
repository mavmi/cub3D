/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_event_handlers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:37:02 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/06 15:10:13 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

// Free all and exit
void	paint_exit(t_painting *painting)
{
	if (painting)
	{
		pars_destroy_map(painting->map);
		mlx_destroy_window(painting->mlx, painting->win);
		free(painting);
	}
	exit(0);
}

int	paint_draw_all(t_painting *painting)
{
	if (!painting)
		return (1);
	if (paint_room_draw_room(painting))
		return (1);
	paint_minimap_draw(painting);
	return (0);
}

// Move player and redraw it
static void	paint_handle_arrows(int key_code, t_painting *painting)
{
	paint_minimap_erase_player(painting);
	if (key_code == LEFT)
		painting->map->player->angle
			= paint_room_decrease_angle(painting->map->player->angle,
				ANGLE_DELTA_KEY);
	else if (key_code == RIGHT)
		painting->map->player->angle
			= paint_room_increase_angle(painting->map->player->angle,
				ANGLE_DELTA_KEY);
	else if (key_code == UP || key_code == W)
		paint_movements_move(painting, MOVE_FORWARD);
	else if (key_code == DOWN || key_code == S)
		paint_movements_move(painting, MOVE_BACK);
	else if (key_code == A)
		paint_movements_move(painting, MOVE_LEFT);
	else if (key_code == D)
		paint_movements_move(painting, MOVE_RIGHT);
	if (paint_draw_all(painting))
		paint_exit(painting);
}

// Keyboard keys handler. Exit on esc and move on arrows
int	paint_key_pressed(int key_code, t_painting *painting)
{
	if (key_code == ESC)
		paint_exit(painting);
	if (key_code == UP || key_code == LEFT
		|| key_code == DOWN || key_code == RIGHT
		|| key_code == W || key_code == A
		|| key_code == S || key_code == D)
		paint_handle_arrows(key_code, painting);
	return (0);
}

// Change player's angle of view relative to north and
// redraw vector of view
int	paint_mouse_move(int x, int y, t_painting *painting)
{
	double			*angle;
	static int		counter = 0;
	static int		previous_x = 0;

	if (x < previous_x)
		counter--;
	else
		counter++;
	previous_x = x;
	if (!counter || counter % PIXELS_PER_DEGREE != 0)
		return (0);
	angle = &painting->map->player->angle;
	if (counter < 0)
		(*angle) = paint_room_decrease_angle(*angle, ANGLE_DELTA_MOUSE);
	else if (counter > 0)
		(*angle) = paint_room_increase_angle(*angle, ANGLE_DELTA_MOUSE);
	counter = 0;
	if (MOUSE_HIDE)
		mlx_mouse_move(painting->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	if (paint_draw_all(painting))
		paint_exit(painting);
	return (y);
}
