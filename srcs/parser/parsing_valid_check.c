/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:14:44 by msalena           #+#    #+#             */
/*   Updated: 2022/02/27 17:35:30 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/arg_parser.h"


static int	all_agrums_got(t_argums *args)
{
	if (args->ud_arr->type_count != 2 || args->txtr_arr->arg_count != 4)
		return (1);
	if (args->txtr_arr->arg[0]->side == NORTH_SIDE_ARG)
	{
		if (args->txtr_arr->arg[1]->side == SOUTH_SIDE_ARG)
		{
			if (args->txtr_arr->arg[2]->side == WEST_SIDE_ARG)
			{
				if (args->txtr_arr->arg[3]->side == EAST_SIDE_ARG)
				{
					if (args->ud_arr->type[0]->type == FLOOR_TYPE)
					{
						if (args->ud_arr->type[1]->type == CEILING_TYPE)
							return (0);
					}
				}
			}
		}
	}
	return (1);
}

static int	check_map(char **arr, int *i_s, size_t *i_e, t_argums *args)
{
	int	map_fl;

	map_fl = map_pars_valid(arr + *i_s);
	if(map_fl < 0)
		*i_s = map_fl;
	else
		*i_s += map_fl;
	*i_e = 0;
	if (*i_s < 0)
	{
		printf("3\n");
		return (error_destroy(args, 'n'));
	}
	while (arr[*i_s] && arr[*i_s][*i_e] == '\0')
	{
		i_s++;
	}
	if (arr[*i_s] || all_agrums_got(args)
	{
		printf("4\n");
		return (error_destroy(args, 'y'));
	}
	return (0);
}

static int	check_every_str(char **arr, int *i_s, size_t *i_e, t_argums *args)
{
	if (arr[*i_s][*i_e] == NO_SIDE || arr[*i_s][*i_e] == SO_SIDE
			|| arr[*i_s][*i_e] == WE_SIDE || arr[*i_s][*i_e] == EA_SIDE)
	{
		//"take new texture elem" function: give me arr[i_s + i_e]
		if (pars_valid_txtr((arr[*i_s] + i_e), args->txtr_arr))
		{
			printf("1\n");
			return (error_destroy(args, 'n')); //don't forget free()
		}
	}
	else if (arr[*i_s][*i_e] == FLOOR || arr[*i_s][*i_e] == CEILING)
	{
		//"take new up_back elem" function: give me arr[i_s + i_e]
		if (pars_valid_up_down((arr[*i_s] + i_e), args->ud_arr))
		{
			printf("2\n");
			return (error_destroy(args, 'n')); //don't forget free()
		}
	}
	else if (arr[*i_s][*i_e] == MAP_SQ_EMPTY || arr[*i_s][*i_e] == MAP_SQ_WALL
				|| arr[*i_s][*i_e] == MAP_OR_NORTH || arr[*i_s][*i_e] == MAP_OR_SOUTH
				|| arr[*i_s][*i_e] == MAP_OR_EAST || arr[*i_s][*i_e] == MAP_OR_WEST)
	{
		//"for map" function: give me (arr + i_s)
		if (check_map(arr, i_s, i_e, args))
		{
			return (1);
		}
		// int	map_fl;

		// map_fl = map_pars_valid(arr + i_s);
		// if(map_fl < 0)
		// 	i_s = map_fl;
		// else
		// 	i_s += map_fl;
		// i_e = 0;
		// if (i_s < 0)
		// {
		// 	printf("3\n");
		// 	return (error_destroy(args, 'n'));//don't forget free()
		// }
		// while (arr[i_s] && arr[i_s][i_e] == '\0')
		// {
		// 	i_s++;
		// }
		// if (arr[i_s] || all_agrums_got(ud_arr, txtr_arr))
		// {
		// 	printf("4\n");
		// 	return (error_destroy(args, 'y'));//don't forget free()
		// }
		///tmp///
		pars_destroy_up_down(args->ud_arr);
		pars_destroy_textures(args->txtr_arr);
		return (0);
	}
	else
	{
		printf("5\n");
		return (error_destroy(argums, 'y'));//don't forget free()
	}
	return (0);
}

int	pars_arg_definition(char **arr)
{
	int		i_s;
	size_t		i_e;
	t_up_down	*ud_arr;
	t_textures	*txtr_arr;
	t_argums	argums;

	if (!arr)
		return (1);
	ud_arr = pars_get_empty_up_down();
	txtr_arr = pars_get_empty_textures();
	if (!ud_arr || !txtr_arr)
		return (error_destroy(argums, 'n'));
	argums.ud_arr = ud_arr;
	argums.txtr_arr = txtr_arr;
	i_s = 0;
	i_e = 0;
	while (arr[i_s])
	{
		while (arr[i_s][i_e] == SKIP_SPACE)
		{
			i_e++;
		}
		if (arr[i_s][i_e] == '\0')
		{
			i_e = 0;
		}
		if (check_every_str(arr, &i_s, &i_e, argums))
			return (1);
		// else if (arr[i_s][i_e] == NORTH_SIDE_ARG || arr[i_s][i_e] == SOUTH_SIDE_ARG
		// 	|| arr[i_s][i_e] == WEST_SIDE_ARG || arr[i_s][i_e] == EAST_SIDE_ARG)
		// {
		// 	//"take new texture elem" function: give me arr[i_s + i_e]
		// 	if (pars_valid_txtr((arr[i_s] + i_e), txtr_arr))
		// 	{
		// 		printf("1\n");
		// 		return (error_destroy('n')); //don't forget free()
		// 	}
		// }
		// else if (arr[i_s][i_e] == FLOOR_TYPE || arr[i_s][i_e] == CEILING_TYPE)
		// {
		// 	//"take new up_back elem" function: give me arr[i_s + i_e]
		// 	if (pars_valid_up_down((arr[i_s] + i_e), ud_arr))
		// 	{
		// 		printf("2\n");
		// 		return (error_destroy('n')); //don't forget free()
		// 	}
		// }
		// else if (arr[i_s][i_e] == MAP_SQ_EMPTY || arr[i_s][i_e] == MAP_SQ_WALL
		// 			|| arr[i_s][i_e] == MAP_OR_NORTH || arr[i_s][i_e] == MAP_OR_SOUTH
		// 			|| arr[i_s][i_e] == MAP_OR_EAST || arr[i_s][i_e] == MAP_OR_WEST)
		// {
		// 	//"for map" function: give me (arr + i_s)
		// 	int	map_fl;

		// 	map_fl = map_pars_valid(arr + i_s);
		// 	if(map_fl < 0)
		// 		i_s = map_fl;
		// 	else
		// 		i_s += map_fl;
		// 	i_e = 0;
		// 	if (i_s < 0)
		// 	{
		// 		printf("3\n");
		// 		return (error_destroy('n'));//don't forget free()
		// 	}
		// 	while (arr[i_s] && arr[i_s][i_e] == '\0')
		// 	{
		// 		i_s++;
		// 	}
		// 	if (arr[i_s] || all_agrums_got(ud_arr, txtr_arr))
		// 	{
		// 		printf("4\n");
		// 		return (error_destroy('y'));//don't forget free()
		// 	}
		// 	///tmp///
		// 	pars_destroy_up_down(ud_arr);
		// 	pars_destroy_textures(txtr_arr);
		// 	return (0);
		// }

		i_e = 0;
		i_s++;
	}
	printf("6\n");
	return (error_destroy (argums, 'y'));
}
