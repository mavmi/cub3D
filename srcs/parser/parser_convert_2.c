/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_convert_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:42:33 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/13 22:13:05 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static t_map_line	*pars_str_to_map_line_handler(t_map *map,
						t_map_line *map_line, char *str, int y)
{
	size_t	x;

	x = 0;
	while (x < map_line->width)
	{
		map_line->line[x] = pars_char_to_square(map, str[x], x, y);
		if (!map_line->line[x])
		{
			pars_destroy_map_line(map_line);
			return (NULL);
		}
		x++;
	}
	map_line->line[x] = NULL;
	return (map_line);
}

t_map_line	*pars_str_to_map_line(t_map *map, char *str, int y)
{
	t_map_line	*map_line;

	if (!map || !str || y < 0 || !pars_is_str_valid(str))
		return (NULL);
	map_line = pars_get_empty_map_line();
	if (!map_line)
		return (NULL);
	map_line->width = ft_strlen(str);
	map_line->line = (t_square **)malloc(sizeof(t_square *)
			* (map_line->width + 1));
	if (!map_line->line)
	{
		pars_destroy_map_line(map_line);
		return (NULL);
	}
	return (pars_str_to_map_line_handler(map, map_line, str, y));
}

static t_map	*pars_str_arr_to_map_handler(t_map *map, char **arr)
{
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		map->lines[y] = pars_str_to_map_line(map, arr[y], y);
		if (!map->lines[y])
		{
			pars_destroy_map(map);
			return (NULL);
		}
		y++;
	}
	map->lines[y] = NULL;
	return (map);
}

t_map	*pars_str_arr_to_map(char **arr)
{
	t_map	*map;

	if (!arr)
		return (NULL);
	map = pars_get_empty_map();
	if (!map)
		return (NULL);
	map->height = utils_get_str_arr_size(arr);
	map->lines = (t_map_line **)malloc(sizeof(t_map_line *)
			* (map->height + 1));
	if (!map->lines)
	{
		pars_destroy_map(map);
		return (NULL);
	}
	return (pars_str_arr_to_map_handler(map, arr));
}
