/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_valid_check_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:32:50 by msalena           #+#    #+#             */
/*   Updated: 2022/03/19 15:46:51 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

static int	right_side(char **arr, size_t i_arr,
						size_t i_str, t_param_len *lens)
{
	if (arr[i_arr][i_str + 1]
		&& (arr[i_arr][i_str + 1] != ' ' && arr[i_arr][i_str + 1] != '1'))
		return (1);
	if (lens->up && i_str < (lens->up - 1)
		&& (arr[i_arr - 1][i_str + 1] != ' '
		&& arr[i_arr - 1][i_str + 1] != '1'))
		return (1);
	if (lens->down && i_str < (lens->down - 1)
		&& (arr[i_arr + 1][i_str + 1] != ' '
		&& arr[i_arr + 1][i_str + 1] != '1'))
		return (1);
	return (0);
}

static int	left_side(char **arr, size_t i_arr,
						size_t i_str, t_param_len *lens)
{
	if (i_str != 0 && (arr[i_arr][i_str - 1] != ' '
		&& arr[i_arr][i_str - 1] != '1'))
		return (1);
	if (i_str != 0 && lens->up && i_str <= (lens->up - 1)
		&& (arr[i_arr - 1][i_str - 1] != ' '
		&& arr[i_arr - 1][i_str - 1] != '1'))
		return (1);
	if (i_str != 0 && lens->down && i_str <= (lens->down - 1)
		&& (arr[i_arr + 1][i_str - 1] != ' '
		&& arr[i_arr + 1][i_str - 1] != '1'))
		return (1);
	return (0);
}

/*
	Check all characters around: up, down, left & right sides
*/
int	map_check_valid_spaces(char **arr, size_t i_arr,
						size_t i_str, t_param_len *lens)
{
	if (lens->up && i_str <= (lens->up - 1)
		&& (arr[i_arr - 1][i_str] != ' ' && arr[i_arr - 1][i_str] != '1'))
		return (errors(MAP));
	if (lens->down && i_str <= (lens->down - 1)
		&& (arr[i_arr + 1][i_str] != ' ' && arr[i_arr + 1][i_str] != '1'))
		return (errors(MAP));
	if (right_side(arr, i_arr, i_str, lens))
		return (errors(MAP));
	if (left_side(arr, i_arr, i_str, lens))
		return (errors(MAP));
	return (0);
}

int	map_check_valid_doors(char **arr, size_t i_arr,
						size_t i_str, t_param_len *lens)
{
	if (i_str > (lens->up - 1) || i_str > (lens->down - 1)
		|| !arr[i_arr][i_str + 1])
		return (errors(MAP));
	if (arr[i_arr - 1][i_str] == '1')
	{
		if (arr[i_arr + 1][i_str] == '1' && arr[i_arr][i_str - 1] != '1'
			&& arr[i_arr][i_str + 1] != '1')
			return (0);
	}
	else if (arr[i_arr][i_str - 1] == '1')
	{
		if (arr[i_arr][i_str + 1] == '1' && arr[i_arr - 1][i_str] != '1'
			&& arr[i_arr + 1][i_str] != '1')
			return (0);
	}
	return (errors(MAP));
}
