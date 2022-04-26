/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_floor_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:43:03 by msalena           #+#    #+#             */
/*   Updated: 2022/03/19 16:11:49 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

static void	*add_new_ud_elem(size_t *rgb, char *str, t_up_down *arr)
{
	size_t		i;
	t_ud_type	*new;

	new = pars_get_new_ud_type(str[0], rgb[0], rgb[1], rgb[2]);
	if (!new)
		return (free_return(rgb, 'n', FC));
	i = 0;
	if (arr->type_count == 2)
	{
		free(new);
		return (free_return(rgb, 'y', FC));
	}
	while (i < arr->type_count)
	{
		if (new->type == arr->type[i]->type)
		{
			free(new);
			return (free_return(rgb, 'y', FC));
		}
		i++;
	}
	arr->type[arr->type_count] = new;
	arr->type_count++;
	return (new);
}

static void	*check_valid_rgb_str(size_t *rgb_arr, char *tmp, char *s, size_t i)
{
	size_t	i_rgb;
	int		new_el;

	i_rgb = 0;
	while (s[i])
	{
		if (i_rgb >= 3)
		{
			if (s[i++] == SKIP_SPACE)
				continue ;
			return (free_return(rgb_arr, 'y', FC));
		}
		new_el = ft_atoi(s + i);
		if (new_el < 0 || new_el > 255 || (new_el == 0 && s[i] != '0'
				&& ((s[i] == ',' && i == 0) || (s[i] == ',' && s[i + 1] == '\0')
					|| (s[i] == ',' && s[i + 1] == ','))))
			return (free_return(rgb_arr, 'y', FC));
		if (s[i] != ',')
			rgb_arr[i_rgb++] = (size_t)new_el;
		tmp = ft_itoa(new_el);
		i += ft_strlen(tmp);
		free (tmp);
	}
	return (rgb_arr);
}

static size_t	*creat_arr_rgb(char *str)
{
	size_t	i_rgb;
	size_t	*rgb_arr;
	char	*tmp;

	i_rgb = 0;
	tmp = NULL;
	rgb_arr = (size_t *)malloc(sizeof(size_t) * 4);
	if (!rgb_arr)
		return (free_return(NULL, 'n', FC));
	while (i_rgb < 4)
		rgb_arr[i_rgb++] = '\0';
	if (!check_valid_rgb_str(rgb_arr, tmp, str, 0))
		return (NULL);
	return (rgb_arr);
}

int	pars_valid_up_down(char *str, t_up_down *arr)
{
	size_t	i;
	size_t	*rgb;

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
	rgb = creat_arr_rgb(str + i);
	if (!rgb)
		return (1);
	if (!add_new_ud_elem(rgb, str, arr))
	{
		free(rgb);
		return (1);
	}
	free(rgb);
	return (0);
}
