/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_convert_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:43:34 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/27 19:16:53 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// Check if current char is player's char.
// Update map's player struct if it is
static void	pars_is_player(t_map *map, char c, int x, int y)
{
	if (!map || !pars_is_char_valid_player(c) || x < 0 || y < 0)
		return ;
	map->player = pars_get_empty_player();
	if (!map->player)
		return ;
	map->player->pos->x = (double)x + 0.5;
	map->player->pos->y = (double)y + 0.5;
	map->player->orient = c;
	if (c == MAP_OR_NORTH)
		map->player->angle = 0;
	else if (c == MAP_OR_SOUTH)
		map->player->angle = 180;
	else if (c == MAP_OR_EAST)
		map->player->angle = 90;
	else if (c == MAP_OR_WEST)
		map->player->angle = 270;
}

// Convert file's char to t_square.
// May return NULL
t_square	*pars_char_to_square(t_map *map, char c, int x, int y)
{
	t_square	*square;

	if (!map || !pars_is_char_valid(c) || x < 0 || y < 0)
		return (NULL);
	square = pars_get_empty_square();
	if (!square)
		return (NULL);
	square->top_left_x = x;
	square->top_left_y = y;
	if (pars_is_char_valid_player(c))
		square->type = MAP_SQ_EMPTY;
	else
		square->type = c;
	pars_is_player(map, c, x, y);
	return (square);
}
