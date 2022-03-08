/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_floor_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:43:03 by msalena           #+#    #+#             */
/*   Updated: 2022/03/08 14:29:23 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

static void	*add_new_ud_elem(size_t *RGB, char *str, t_up_down *arr)
{
	size_t		i;
	t_ud_type	*new;

	new = pars_get_new_ud_type(str[0], RGB[0], RGB[1], RGB[2]);
	if (!new)
		return (free_return(RGB, 'n', FC));
	i = 0;
	if (arr->type_count == 2)
	{
		free(new);
		return (free_return(RGB, 'y', FC));
	}
	while (i < arr->type_count)
	{
		if (new->type == arr->type[i]->type)
		{
			free(new);
			return (free_return(RGB, 'y', FC));
		}
		i++;
	}
	arr->type[arr->type_count] = new;
	arr->type_count++;
	return (new);
}

static void	*check_valid_RGB_str(size_t *RGB_arr, char *tmp, char *s)
{
	size_t	i;
	size_t	i_RGB;
	int		new_el;

	i = 0;
	i_RGB = 0;
	while (s[i])
	{
		if (i_RGB >= 3)
		{
			if(s[i++] == SKIP_SPACE)
				continue ;
			return (free_return(RGB_arr, 'y', FC));
		}
		new_el = ft_atoi(s + i);
		if (new_el < 0 || new_el > 255 || (new_el == 0 && s[i] != '0'
				&& ((s[i] == ',' && i == 0) || (s[i] == ',' && s[i + 1] == '\0')
				|| (s[i] == ',' && s[i + 1] == ','))))
			return (free_return(RGB_arr, 'y', FC));
		if (s[i] != ',')
			RGB_arr[i_RGB++] = (size_t)new_el;
		tmp = ft_itoa(new_el);
		i += ft_strlen(tmp);
		free (tmp);
	}
	return (RGB_arr);
}

static size_t	*creat_arr_RGB(char *str)
{
	size_t	i_RGB;
	size_t	*RGB_arr;
	char	*tmp;

	i_RGB = 0;
	tmp = NULL;
	RGB_arr = (size_t *)malloc(sizeof(size_t) * 4);
	if (!RGB_arr)
		return (free_return(NULL, 'n', FC));
	while (i_RGB < 4)
		RGB_arr[i_RGB++] = '\0';
	if (!check_valid_RGB_str(RGB_arr, tmp, str))
		return (NULL);
	return (RGB_arr);
}

int	pars_valid_up_down(char *str, t_up_down *arr)
{
	size_t	i;
	size_t	*RGB;

	i = 1;
	if (!str || !arr)
		return (2);
	if (ft_memchr(str, FLOOR, 1) != 0 && ft_memchr(str, CEILING, 1) != 0)
		return (errors(FC));
	while (str[i] == SKIP_SPACE)
		i++;
	if (!str[i])
		return (errors(FC));
	if (check_other_three_elems(str + i))
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
