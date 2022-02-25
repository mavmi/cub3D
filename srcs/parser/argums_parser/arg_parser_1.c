/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:14:44 by msalena           #+#    #+#             */
/*   Updated: 2022/02/25 16:42:12 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/arg_parser.h"

int errors()
{
	printf("Error: invalid file arguments\n");
	return (1);
}

static int	all_agrums_got(t_up_down *arr1, t_textures *arr2)
{
	if (arr1->type_count != 2)
		return (error_texture_message());
	if (arr2->arg_count != 4)
		return (error_ud_message());
	return (0);
}

int	pars_arg_definition(char **arr)
{
	size_t		i_s;
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
		printf ("%s\n", arr[i_s]);
		while (arr[i_s][i_e] == SKIP_SPACE)
		{
			i_e++;
		}
		if (arr[i_s][i_e] == NORTH_SIDE_ARG || arr[i_s][i_e] == SOUTH_SIDE_ARG
			|| arr[i_s][i_e] == WEST_SIDE_ARG || arr[i_s][i_e] == EAST_SIDE_ARG)
		{
			//"take new texture elem" function: give me arr[i_s + i_e]
			if (pars_valid_txtr((arr[i_s + i_e]), txtr_arr))
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
			if (pars_valid_up_down(arr[i_s + i_e], ud_arr))
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
			if (map_pars_valid(arr + i_s))
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
