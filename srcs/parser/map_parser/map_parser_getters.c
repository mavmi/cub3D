/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_getters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:10:04 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/12 16:12:47 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

/*
	Create new t_player object and
	fill it with default values.

	May return NULL
*/
t_player	*pars_get_empty_player(void)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = (t_point *)malloc(sizeof(t_point));
	if (!player->pos)
	{
		free(player);
		return (NULL);
	}
	player->pos->x = BAD_PL_POS;
	player->pos->y = BAD_PL_POS;
	player->orient = BAD_PL_ORIENT;
	player->angle = BAD_PL_ANGLE;
	return (player);
}

/*
	Create new t_square object and
	fill it with default values.

	May return NULL
*/
t_square	*pars_get_empty_square(void)
{
	t_square	*square;

	square = (t_square *)malloc(sizeof(t_square));
	if (!square)
		return (NULL);
	square->top_left_x = BAD_SQ_POS;
	square->top_left_y = BAD_SQ_POS;
	square->type = BAD_SQ_TYPE;
	return (square);
}

/*
	Create new t_map_line object and
	fill it with default values.

	May return NULL
*/
t_map_line	*pars_get_empty_map_line(void)
{
	t_map_line	*map_line;

	map_line = (t_map_line *)malloc(sizeof(t_map_line));
	if (!map_line)
		return (NULL);
	map_line->width = 0;
	map_line->line = NULL;
	return (map_line);
}

// Create new t_map object and
// fill it with default values.

// May return NULL
t_map	*pars_get_empty_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 0;
	map->player = NULL;
	map->lines = NULL;
	map->argms = NULL;
	return (map);
}
