/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_destroyers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:14:05 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/13 17:56:11 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

/*
	Free t_player
*/
void	pars_destroy_player(t_player *player)
{
	if (!player)
		return ;
	free(player->pos);
	free(player);
}

/*
	Free t_square
*/
void	pars_destroy_square(t_square *square)
{
	if (!square)
		return ;
	free(square);
}

/*
	Free t_map_line
*/
void	pars_destroy_map_line(t_map_line *map_line)
{
	size_t	i;

	if (!map_line)
		return ;
	if (map_line->line)
	{
		i = 0;
		while (map_line->line[i])
		{
			pars_destroy_square(map_line->line[i]);
			i++;
		}
		free(map_line->line);
	}
	free(map_line);
}

/*
	Free t_map
*/
void	pars_destroy_map(t_map *map)
{
	size_t	i;

	if (!map)
		return ;
	if (map->lines)
	{
		i = 0;
		while (map->lines[i])
		{
			pars_destroy_map_line(map->lines[i]);
			i++;
		}
		free(map->lines);
	}
	pars_destroy_player(map->player);
	pars_destroy_argums(map->argms);
	free(map);
}
