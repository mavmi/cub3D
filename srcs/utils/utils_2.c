/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:52:10 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/26 14:59:26 by pmaryjo          ###   ########.fr       */
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
