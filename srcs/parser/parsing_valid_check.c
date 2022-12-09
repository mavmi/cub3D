/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_valid_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:14:44 by msalena           #+#    #+#             */
/*   Updated: 2022/03/19 16:34:09 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	all_agrums_got(t_argums *args)
{
	if (args->ud_arr->type_count != 2 || args->txtr_arr->arg_count != 4)
		return (1);
	if (args->txtr_arr->arg[0]->side == NO_SIDE)
	{
		if (args->txtr_arr->arg[1]->side == SO_SIDE)
		{
			if (args->txtr_arr->arg[2]->side == WE_SIDE)
			{
				if (args->txtr_arr->arg[3]->side == EA_SIDE)
				{
					if (args->ud_arr->type[0]->type == FLOOR)
					{
						if (args->ud_arr->type[1]->type == CEILING)
						{
							if (!(take_memory_for_txtrs(args->txtr_arr)))
								return (0);
						}
					}
				}
			}
		}
	}
	return (1);
}

static int	check_map(char **arr, int *i_s, int *i_e, t_argums *args)
{
	int	map_fl;

	map_fl = map_pars_valid(arr + *i_s);
	if (map_fl < 0)
		*i_s = map_fl;
	else
		*i_s += map_fl;
	*i_e = 0;
	if (*i_s < 0)
	{
		return (error_destroy(args, 'n'));
	}
	while (arr[*i_s] && arr[*i_s][*i_e] == '\0')
	{
		(*i_s)++;
	}
	if (arr[*i_s] || all_agrums_got(args))
	{
		return (error_destroy(args, 'y'));
	}
	return (0);
}

static int	check_every_str(char **arr, int *i_s, int *i_e, t_argums *args)
{
	if (arr[*i_s][*i_e] == '\0')
		*i_e = 0;
	else if (arr[*i_s][*i_e] == NO_SIDE || arr[*i_s][*i_e] == SO_SIDE
			|| arr[*i_s][*i_e] == WE_SIDE || arr[*i_s][*i_e] == EA_SIDE)
	{
		if (pars_valid_txtr((arr[*i_s] + *i_e), args->txtr_arr))
			return (error_destroy(args, 'n'));
	}
	else if (arr[*i_s][*i_e] == FLOOR || arr[*i_s][*i_e] == CEILING)
	{
		if (pars_valid_up_down((arr[*i_s] + *i_e), args->ud_arr))
			return (error_destroy(args, 'n'));
	}
	else if (arr[*i_s][*i_e] == MAP_SQ_EMPTY || arr[*i_s][*i_e] == MAP_OR_SOUTH
			|| arr[*i_s][*i_e] == MAP_OR_NORTH || arr[*i_s][*i_e] == MAP_OR_EAST
			|| arr[*i_s][*i_e] == MAP_SQ_WALL || arr[*i_s][*i_e] == MAP_OR_WEST)
	{
		args->map_start = *i_s;
		if (check_map(arr, i_s, i_e, args))
			return (1);
		return (-1);
	}
	else
		return (error_destroy(args, 'y'));
	return (0);
}

static int	take_memory_argums(t_argums *argums)
{
	if (!argums)
		return (1);
	argums->ud_arr = pars_get_empty_up_down();
	argums->txtr_arr = pars_get_empty_textures();
	argums->map_start = 0;
	if (!argums->ud_arr || !argums->txtr_arr)
		return (error_destroy(argums, 'n'));
	return (0);
}

t_argums	*pars_arg_definition(char **arr)
{
	int			i_s;
	int			i_e;
	t_argums	*argums;

	if (!arr)
		return (NULL);
	argums = (t_argums *)malloc(sizeof(t_argums) * 2);
	if (take_memory_argums(argums))
		return (NULL);
	i_s = 0;
	i_e = 0;
	while (arr[i_s])
	{
		while (arr[i_s][i_e] == SKIP_SPACE)
			i_e++;
		i_e = check_every_str(arr, &i_s, &i_e, argums);
		if (i_e == 1)
			return (NULL);
		else if (i_e == -1)
			return (argums);
		i_e = 0;
		if (arr[i_s])
			i_s++;
	}
	return (free_return (argums, 'y', ALL));
}
