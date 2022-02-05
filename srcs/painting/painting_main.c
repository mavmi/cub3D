/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:25:05 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/05 18:48:05 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

static t_painting	*paint_get_struct(t_map *map)
{
	t_painting	*p;

	p = (t_painting *)malloc(sizeof(t_painting));
	if (!p)
		return (NULL);
	p->map = map;
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIN_WIDTH, WIN_HEIGHT, "etozhe_cub3D");
	p->minimap.img = mlx_new_image(p->mlx, MAP_WIDTH, MAP_HEIGHT);
	p->room.img = mlx_new_image(p->mlx, WIN_WIDTH, WIN_HEIGHT);
	p->minimap.img_addr = mlx_get_data_addr(p->minimap.img,
			&p->minimap.bits_per_pixel, &p->minimap.size_line,
			&p->minimap.endian);
	p->room.img_addr = mlx_get_data_addr(p->room.img,
			&p->room.bits_per_pixel, &p->room.size_line,
			&p->room.endian);
	return (p);
}

static int	paint_a(void *data)
{
	t_painting	*painting;

	painting = (t_painting *)data;
	paint_exit(painting);
	return (1);
}

static void	paint_set_up_handlers(t_painting *painting)
{
	mlx_put_image_to_window(painting->mlx, painting->win,
		painting->minimap.img, 0, 0);
	mlx_put_image_to_window(painting->mlx, painting->win,
		painting->room.img, 0, 0);
	mlx_hook(painting->win, 2, 1L << 0, paint_key_pressed, painting);
	mlx_hook(painting->win, 6, 1L << 6, paint_mouse_move, painting);
	mlx_hook(painting->win, 17, 0L, paint_a, painting);
	if (MOUSE_HIDE)
		mlx_mouse_hide();
}

// Init t_painting struct, create window,
// set up input handlers and loop mlx
void	paint(t_map *map)
{
	t_painting	*painting;

	if (!map)
		exit(1);
	painting = paint_get_struct(map);
	if (!painting)
	{
		pars_destroy_map(map);
		exit(1);
	}
	paint_set_up_handlers(painting);
	paint_minimap_draw_map(painting);
	paint_draw_all(painting);
	mlx_loop(painting->mlx);
}
