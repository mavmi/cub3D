/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_floor_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:43:03 by msalena           #+#    #+#             */
/*   Updated: 2022/02/27 17:43:23 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/arg_parser.h"

static void	*add_new_ud_elem(size_t *RGB, char *str, t_up_down *arr)
{
	size_t		i;
	t_ud_type	*new;

	new = pars_get_new_ud_type(str[0], RGB[0], RGB[1], RGB[2]);
	if (!new)
		return (free_return(RGB, 'n'));
	i = 0;
	if (arr->type_count == 2)
	{
		free(new);
		return (free_return(RGB, 'y'));
	}
	while (i < arr->type_count)
	{
		if (new->type == arr->type[i]->type)
		{
			free(new);
			return (free_return(RGB, 'y'));
		}
		i++;
	}
	arr->type[arr->type_count] = new;
	arr->type_count++;
	return (new);
}

static size_t	*creat_arr_RGB(char *str)
{
	size_t	i_str;
	size_t	i_RGB;
	int		new_elem;
	size_t	*RGB_arr;

	i_str = 0;
	i_RGB = 0;
	///////
	RGB_arr = (size_t *)malloc(sizeof(size_t) * 4);
	if (!RGB_arr)
		return (free_return(NULL, 'n'));
	while (i_RGB < 4)
		RGB_arr[i_RGB++] = '\0';
	i_RGB = 0;
	////////
	char	*tmp;

	tmp = NULL;
	while (str[i_str])
	{
		if (i_RGB >= 3)
		{
			if(str[i_str++] == SKIP_SPACE)
				continue ;
			return (free_return(RGB_arr, 'y'));
		}
		new_elem = ft_atoi(str + i_str);
		if (new_elem < 0 || new_elem > 255 || (new_elem == 0
				&& str[i_str] != '0'
				&& ((str[i_str] == ',' && i_str == 0)
				|| (str[i_str] == ',' && str[i_str + 1] == '\0')
				|| (str[i_str] == ',' && str[i_str + 1] == ','))))
		{
			return (free_return(RGB_arr, 'y'));
		}
		if (str[i_str] != ',')
			RGB_arr[i_RGB++] = (size_t)new_elem;
		tmp = ft_itoa(new_elem);
		i_str += ft_strlen(tmp);
		free (tmp);
	}

	return (RGB_arr);
}

int	pars_valid_up_down(char *str, t_up_down *arr)
{
	size_t	i;
	size_t	*RGB;

	i = 1;
	if (!str || !arr)
		return (2);
	if (ft_memchr(str, FLOOR_TYPE, 1) != 0 && ft_memchr(str, CEILING_TYPE, 1) != 0)
		return (error_ud_message());
	while (str[i] == SKIP_SPACE)
		i++;
	if (!str[i])
		return (error_ud_message());
	if (check_other_three_elems(str + i)) //other three digit protection
		return (1);
	RGB = creat_arr_RGB(str + i);
	if (!RGB)
	{
		return (1);
	}
	if (!add_new_ud_elem(RGB, str, arr))
		return (1);
	return (0);
}
