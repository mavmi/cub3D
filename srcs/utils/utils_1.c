/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:22:21 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/08 16:35:58 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

double	utils_degree_to_rad(double degree)
{
	return (degree * M_PI / 180.0);
}

double	utils_rad_to_degree(double rad)
{
	return (rad * 180.0 / M_PI);
}

/*
	Get size of array of strings
*/
size_t	utils_get_str_arr_size(char **arr)
{
	size_t	size;

	if (!arr)
		return (0);
	size = 0;
	while (*arr)
	{
		size++;
		arr++;
	}
	return (size);
}

/*
	Free array of strings
*/
void	utils_destroy_str_arr(char **arr)
{
	char	**ptr;

	if (!arr)
		return ;
	ptr = arr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(arr);
}

/*
	Append strings array arr with string str.
	Return 0 if everything is ok,
	1 otherwise
*/
int	utils_str_arr_push_bach(char ***arr, char *str)
{
	int		i;
	char	**new_arr;

	if (!arr || !str)
		return (1);
	new_arr = (char **)malloc(sizeof(char *)
			* (utils_get_str_arr_size(*arr) + 2));
	if (!new_arr)
		return (1);
	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
		{
			new_arr[i] = (*arr)[i];
			i++;
		}
	}
	new_arr[i++] = str;
	new_arr[i] = NULL;
	free(*arr);
	*arr = new_arr;
	return (0);
}
