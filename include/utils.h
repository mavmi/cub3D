/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:15:03 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/26 14:59:31 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// utils_1.c
size_t	utils_get_str_arr_size(char **arr);
void	utils_destroy_str_arr(char **arr);
int		utils_str_arr_push_bach(char ***arr, char *str);

// utils_2.c
double	utils_degree_to_rad(double degree);
double	utils_rad_to_degree(double rad);

#endif
