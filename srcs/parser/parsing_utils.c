/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:48:43 by msalena           #+#    #+#             */
/*   Updated: 2022/03/05 19:22:14 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_parser.h"

/*
	Checks the floor and ceiling digit colors
	aren't bigger then three ints (hundredth place)
*/
int	check_other_three_elems(char *str)
{
	size_t	i_str;
	size_t	i_int;

	if (!str)
		return (2);
	i_str = 0;
	i_int = 0;
	while (str[i_str])
	{
		while (str[i_str] >= '0' && str[i_str++] <= '9')
			i_int++;
		if (i_int > 3)
			return (error_ud_message());
		i_int = 0;
		i_str++;
	}
	return (0);
}

/*
	Free freed and input sms about
	invalide argums if sms_fl == 'y'
*/
void	*free_return(size_t *freed, char sms_fl)
{
	if (sms_fl && sms_fl == 'y')
		error_ud_message();
	free(freed);
	return (NULL);
}

size_t	arr_size_before_empty_str(char **arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (len);
	while (arr[len][0])
	{
		len++;
	}
	return (len);
}
