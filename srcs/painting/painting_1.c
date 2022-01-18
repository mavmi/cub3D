/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:25:05 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/18 17:53:52 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

static void	paint_exit(t_painting *painting)
{
	if (!painting)
		return ;
	pars_destroy_map(painting->map);
	mlx_destroy_window(painting->mlx, painting->win);
	free(painting);
	exit(0);
}

static void	paint_handle_arrows(int key_code, t_painting *painting)
{
	paint_draw_player(painting, FIELD_COLOR);
	if (key_code == LEFT)
		paint_move_left(painting);
	else if (key_code == RIGHT)
		paint_move_right(painting);
	else if (key_code == UP)
		paint_move_up(painting);
	else if (key_code == DOWN)
		paint_move_down(painting);
	paint_draw_player(painting, PLAYER_COLOR);
}

static int	paint_key_pressed(int key_code, t_painting *painting)
{
	if (key_code == ESC)
		paint_exit(painting);
	if (key_code == LEFT || key_code == RIGHT
		|| key_code == UP || key_code == DOWN)
		paint_handle_arrows(key_code, painting);
	return (0);
}

static int	paint_mouse_move(int x, int y, t_painting *painting)
{
	int				*angle;
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
	paint_print_ray(painting);
	return (0);
}

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
	painting->win = mlx_new_window(painting->mlx, WIDTH, HEIGHT, "cub2D");
	mlx_hook(painting->win, 2, 1L << 0, paint_key_pressed, painting);
	mlx_hook(painting->win, 6, 1L << 6, paint_mouse_move, painting);
	paint_draw_map(painting);
	paint_draw_player(painting, PLAYER_COLOR);
	mlx_loop(painting->mlx);
}
