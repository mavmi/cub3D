/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_convert_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:43:34 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/14 15:06:02 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

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
	if (c == NORTH_OR)
		map->player->angle = 0.0;
	else if (c == SOUTH_OR)
		map->player->angle = 180.0;
	else if (c == EAST_OR)
		map->player->angle = 90.0;
	else if (c == WEST_OR)
		map->player->angle = 270.0;
}

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
		square->type = EMPTY;
	else
		square->type = c;
	pars_is_player(map, c, x, y);
	return (square);
}
