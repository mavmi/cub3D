/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:14:44 by msalena           #+#    #+#             */
/*   Updated: 2022/02/13 19:00:04 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/arg_parser.h"

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
	txtr_arr = pars_get_empty_tetures();
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
			if (take_valid_txtr((arr[i_s + i_e]), txtr_arr))
				return (1);
		}
		else if (arr[i_s][i_e] == FLOOR_TYPE || arr[i_s][i_e] == CEILING_TYPE)
		{
			//"take new up_back elem" function: give me arr[i_s + i_e]
		}
		else if (arr[i_s][i_e] == MAP_SQ_EMPTY || arr[i_s][i_e] == MAP_SQ_WALL
					|| arr[i_s][i_e] == MAP_OR_NORTH || arr[i_s][i_e] == MAP_OR_SOUTH
					|| arr[i_s][i_e] == MAP_OR_EAST || arr[i_s][i_e] == MAP_OR_WEST)
		{
			//"for map" function
		}
		else if (arr[i_s][i_e] == '\n')
		{
			// continue ;
		}
		else
		{
			// return with error
		}
		i_e = 0;
		i_s++;
	}
}
