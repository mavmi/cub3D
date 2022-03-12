/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:25:05 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/12 16:12:56 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

static int	paint_load_images(t_painting *p)
{
	p->t_north = paint_get_image(p, p->map->argms->txtr_arr->arg[0]->path);
	p->t_south = paint_get_image(p, p->map->argms->txtr_arr->arg[1]->path);
	p->t_west = paint_get_image(p, p->map->argms->txtr_arr->arg[2]->path);
	p->t_east = paint_get_image(p, p->map->argms->txtr_arr->arg[3]->path);
	p->t_door = paint_get_image(p, p->map->argms->txtr_arr->arg[4]->path);
	if (!p->t_north || !p->t_south || !p->t_west || !p->t_east || !p->t_door)
	{
		return (1);
	}
	return (0);
}

static t_painting	*paint_get_struct(t_map *map)
{
	t_painting	*p;
	t_ud_type	**c;

	p = (t_painting *)malloc(sizeof(t_painting));
	if (!p)
		return (NULL);
	c = map->argms->ud_arr->type;
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
	p->minimap_x = (int)p->map->player->pos->x * MAP_SQ_SIZE;
	p->minimap_y = (int)p->map->player->pos->y * MAP_SQ_SIZE;
	p->floor = (int)((((c[0]->red << 8) + c[0]->green) << 8) + c[0]->blue);
	p->ceil = (int)((((c[1]->red << 8) + c[1]->green) << 8) + c[1]->blue);
	if (paint_load_images(p))
		paint_exit(p);
	return (p);
}

/*
	Little red cross in the corner of window
*/
static int	paint_cross(void *data)
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
	mlx_hook(painting->win, 17, 0L, paint_cross, painting);
	if (MOUSE_HIDE)
		mlx_mouse_hide();
}

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
	painting->cl_door_fl = 0;
	paint_set_up_handlers(painting);
	paint_minimap_draw_map(painting);
	paint_minimap_draw(painting);
	paint_draw_all(painting);
	mlx_loop(painting->mlx);
}
