/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:25:05 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 16:42:12 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

// Free all and exit
static void	paint_exit(t_painting *painting)
{
	if (!painting)
		return ;
	pars_destroy_map(painting->map);
	mlx_destroy_window(painting->mlx, painting->win);
	free(painting);
	exit(0);
}

// Move player and redraw it
static void	paint_handle_arrows(int key_code, t_painting *painting)
{
	if (key_code == LEFT || key_code == A)
		painting->map->player->angle
			= paint_room_decrease_angle(painting->map->player->angle,
				ANGLE_DELTA);
	else if (key_code == RIGHT || key_code == D)
		painting->map->player->angle
			= paint_room_increase_angle(painting->map->player->angle,
				ANGLE_DELTA);
	else if (key_code == UP || key_code == W)
		paint_movements_move_up(painting);
	else if (key_code == DOWN || key_code == S)
		paint_movements_move_down(painting);
	paint_room_draw_room(painting);
}

// Keyboard keys handler. Exit on esc and move on arrows
static int	paint_key_pressed(int key_code, t_painting *painting)
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
static int	paint_mouse_move(int x, int y, t_painting *painting)
{
	double			*angle;
	static int		counter = 0;
	static int		previous_x = 0;

	(void)y;
	if (x < previous_x)
		counter--;
	else
		counter++;
	previous_x = x;
	if (!counter || counter % PIXELS_PER_DEGREE != 0)
		return (0);
	angle = &painting->map->player->angle;
	if (counter < 0 && *angle > ANGLE_DELTA)
		(*angle) -= ANGLE_DELTA;
	else if (counter < 0 && *angle <= ANGLE_DELTA)
		*angle = 360 + *angle - ANGLE_DELTA;
	else if (counter > 0 && *angle <= 360 - ANGLE_DELTA)
		(*angle) += ANGLE_DELTA;
	else if (counter > 0 && *angle > 360 - ANGLE_DELTA)
		*angle = ANGLE_DELTA - (360 - *angle);
	counter = 0;
	if (paint_room_draw_room(painting))
		paint_exit(painting);
	return (0);
}

// Init t_painting struct, create window,
// set up input handlers and loop mlx
void	paint_init(t_map *map)
{
	t_painting	*painting;

	if (!map)
		exit(1);
	painting = (t_painting *)malloc(sizeof(t_painting));
	if (!painting)
	{
		pars_destroy_map(map);
		exit(1);
	}
	painting->map = map;
	painting->mlx = mlx_init();
	painting->win = mlx_new_window(painting->mlx, WIDTH, HEIGHT,
			"etozhe_cub3D");
	painting->img = mlx_new_image(painting->mlx, WIDTH, HEIGHT);
	painting->data_addr = mlx_get_data_addr(painting->img,
			&painting->bits_per_pixel, &painting->size_line, &painting->endian);
	mlx_put_image_to_window(painting->mlx, painting->win, painting->img, 0, 0);
	mlx_hook(painting->win, 2, 1L << 0, paint_key_pressed, painting);
	mlx_hook(painting->win, 6, 1L << 6, paint_mouse_move, painting);
	paint_room_draw_room(painting);
	mlx_loop(painting->mlx);
}
