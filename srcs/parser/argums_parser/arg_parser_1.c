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
	size_t	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i][0] == NORTH_SIDE_ARG || arr[i][0] == SOUTH_SIDE_ARG
				|| arr[i][0] == WEST_SIDE_ARG || arr[i][0] == EAST_SIDE_ARG)
		{
			//"take new texture elem" function
		}
		else if (arr[i][0] == FLOOR_TYPE || arr[i][0] == CEILING_TYPE)
		{
			//"take new up_back elem" function
		}
		else if (arr[i][0] == MAP_SQ_VOID || arr[i][0] == MAP_SQ_EMPTY
					|| arr[i][0] == MAP_SQ_WALL || arr[i][0] == MAP_OR_NORTH
					|| arr[i][0] == MAP_OR_SOUTH || arr[i][0] == MAP_OR_EAST
					|| arr[i][0] == MAP_OR_WEST)
		{
			//"for map" function
		}
		else if (arr[i][0] == '\n')
		{
			// continue ;
		}
		else
		{
			// return with error
		}

	}
}
