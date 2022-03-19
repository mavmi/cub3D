/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:48:43 by msalena           #+#    #+#             */
/*   Updated: 2022/03/19 16:33:11 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	take_memory_for_walls_txtrs(t_textures *txtrs_arr_in, int *iter)
{
	char	*tmp;
	char	*gif_path;

	gif_path = (char *)malloc(sizeof(char)
			* (ft_strlen("./textures/0_gif_pos.xpm") + 2));
	if (!gif_path)
		return (1);
	ft_strlcpy(gif_path, "./textures/\0", (ft_strlen("./textures/") + 1));
	tmp = ft_itoa(*iter);
	ft_strlcat(gif_path, tmp, (ft_strlen("./textures/0_gif_pos.xpm") + 2));
	free(tmp);
	ft_strlcat(gif_path, "_gif_pos.xpm\0",
		(ft_strlen("./textures/0_gif_pos.xpm") + 2));
	if (add_new_side_elem(txtrs_arr_in, gif_path, MAP_SQ_GIF))
		return (1);
	gif_path = NULL;
	(*iter)++;
	return (0);
}

int	take_memory_for_txtrs(t_textures *txtrs_arr_in)
{
	char	*door_path;
	int		iter;

	iter = 1;
	door_path = (char *)malloc(sizeof(char)
			* (ft_strlen("./textures/cl_door.xpm") + 1));
	if (!door_path)
		return (1);
	ft_strlcpy(door_path, "./textures/cl_door.xpm\0",
		(ft_strlen("./textures/cl_door.xpm") + 1));
	if (add_new_side_elem(txtrs_arr_in, door_path, MAP_SQ_CL_DOOR))
		return (1);
	while (iter < 11)
	{
		if (take_memory_for_walls_txtrs(txtrs_arr_in, &iter))
			return (1);
	}
	return (0);
}

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
			return (errors(FC));
		i_int = 0;
		i_str++;
	}
	return (0);
}

/*
	Free freed and input sms about
	invalide argums if sms_fl == 'y'
*/
void	*free_return(void *freed, char sms_fl, t_all code)
{
	if (sms_fl && sms_fl == 'y')
		errors(code);
	free(freed);
	return (NULL);
}

size_t	arr_size_before_empty_str(char **arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (len);
	while (arr[len] && arr[len][0] != '0' && arr[len][0] != '\0')
	{
		len++;
	}
	return (len);
}
