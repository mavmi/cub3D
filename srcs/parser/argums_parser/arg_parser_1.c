/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:14:44 by msalena           #+#    #+#             */
/*   Updated: 2022/02/26 18:39:34 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/arg_parser.h"

int errors()
{
	printf("Error: invalid file's arguments\n");
	return (1);
}

static int	all_agrums_got(t_up_down *arr1, t_textures *arr2)
{
	if (arr1->type_count != 2 || arr2->arg_count != 4)
		return (1);
	return (0);
}

int	pars_arg_definition(char **arr)
{
	int		i_s;
	size_t		i_e;
	t_up_down	*ud_arr;
	t_textures	*txtr_arr;

	if (!arr)
		return (1);
	i_s = 0;
	i_e = 0;
	ud_arr = pars_get_empty_up_down();
	txtr_arr = pars_get_empty_textures();
	while (arr[i_s])
	{
		while (arr[i_s][i_e] == SKIP_SPACE)
		{
			i_e++;
		}
		if (arr[i_s][i_e] == NORTH_SIDE_ARG || arr[i_s][i_e] == SOUTH_SIDE_ARG
			|| arr[i_s][i_e] == WEST_SIDE_ARG || arr[i_s][i_e] == EAST_SIDE_ARG)
		{
			//"take new texture elem" function: give me arr[i_s + i_e]
			if (pars_valid_txtr((arr[i_s] + i_e), txtr_arr))
			{
				pars_destroy_up_down(ud_arr);
				pars_destroy_textures(txtr_arr);
				printf("1\n");
				return (1); //don't forget free()
			}
		}
		else if (arr[i_s][i_e] == FLOOR_TYPE || arr[i_s][i_e] == CEILING_TYPE)
		{
			//"take new up_back elem" function: give me arr[i_s + i_e]
			if (pars_valid_up_down((arr[i_s] + i_e), ud_arr))
			{
				pars_destroy_up_down(ud_arr);
				pars_destroy_textures(txtr_arr);
				printf("2\n");
				return (1); //don't forget free()
			}
		}
		else if (arr[i_s][i_e] == MAP_SQ_EMPTY || arr[i_s][i_e] == MAP_SQ_WALL
					|| arr[i_s][i_e] == MAP_OR_NORTH || arr[i_s][i_e] == MAP_OR_SOUTH
					|| arr[i_s][i_e] == MAP_OR_EAST || arr[i_s][i_e] == MAP_OR_WEST)
		{
			//"for map" function: give me (arr + i_s)
			int	map_fl;

			map_fl = map_pars_valid(arr + i_s);
			if(map_fl < 0)
				i_s = map_fl;
			else
				i_s += map_fl;
			i_e = 0;
			printf("///////////%d\n", i_s);
			if (i_s < 0)
			{
				pars_destroy_up_down(ud_arr);
				pars_destroy_textures(txtr_arr);
				printf("3\n");
				return (1);//don't forget free()
			}
			while (arr[i_s] && arr[i_s][i_e] == '\0')
			{
				i_s++;
			}
			if (arr[i_s] || all_agrums_got(ud_arr, txtr_arr))
			{
				pars_destroy_up_down(ud_arr);
				pars_destroy_textures(txtr_arr);
				printf("4\n");
				return (errors());//don't forget free()
			}
			return (0);
		}
		else if (arr[i_s][i_e] == '\0')
		{
			i_s++;
			continue ;
		}
		else
		{
			pars_destroy_up_down(ud_arr);
			pars_destroy_textures(txtr_arr);
			printf("5\n");
			return (errors());//don't forget free()
		}
		i_e = 0;
		i_s++;
	}
	printf("6\n");
	return (errors());
}
