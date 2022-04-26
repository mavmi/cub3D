/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:15:03 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 16:37:34 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// utils_1.c
double	utils_degree_to_rad(double degree);
double	utils_rad_to_degree(double rad);
size_t	utils_get_str_arr_size(char **arr);
void	utils_destroy_str_arr(char **arr);
int		utils_str_arr_push_bach(char ***arr, char *str);

// utils_2.c
int		utils_is_double_integer(double a);
int		utils_are_doubles_equal(double a, double b);
double	utils_round_double_up(double a);
double	utils_round_double_down(double a);
int		utils_is_greater_or_eq(double a, double b);

#endif
