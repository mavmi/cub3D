/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:52:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/08 16:35:27 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	utils_is_double_integer(double a)
{
	if (utils_are_doubles_equal(a, (int)a))
		return (1);
	return (0);
}

/*
	Return 1 if values are equal, 0 otherwise
*/
int	utils_are_doubles_equal(double a, double b)
{
	if (sqrt(pow(a - b, 2)) < 1e-3)
		return (1);
	return (0);
}

double	utils_round_double_up(double a)
{
	return ((int)a + 1);
}

double	utils_round_double_down(double a)
{
	return ((int)a);
}

/*
	Check if [a] is greater or equal than [b].
	Return 1 if it is, 0 otherwise
*/
int	utils_is_greater_or_eq(double a, double b)
{
	if (utils_are_doubles_equal(a, b) || a > b)
		return (1);
	return (0);
}
