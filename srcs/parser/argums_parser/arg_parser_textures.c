/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:46:29 by marvin            #+#    #+#             */
/*   Updated: 2022/02/14 13:46:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/arg_parser.h"

static int	error_message(void)
{
	printf("Error: invalid texture arguments \n");
	return (1);
}

static char	*take_path(char *str, size_t *start)
{
	char	*path;
	size_t	end;
	size_t	length;

	end = *start;
	while (str[end] && str[end] != SKIP_SPACE)
	{
		end++;
	}
	length = end - start;
	path = (char *)malloc(sizeof(char) * (length + 1));
	if (!path)
		return (NULL);
	ft_memcpy(path, (str + (*start)), length);
	if (path[length - 1] != '\0')
		path[length] = '\0';
	*start = end;
	return (path);
}

static int	add_new_side_elem(t_textures *arr, char *path, char side)
{
	size_t		i;
	t_txtr_arg	*new;

	i = 0;
	new = pars_get_new_txtr_arg(side, path);
	if (!new)
		return (2);
	if (arr->arg_count == 4)
	{
		return (error_message());
	}
	while (i < arr->arg_count)
	{
		if (new->side == arr->arg[i]->side)
			return (error_message());
		i++;
	}
	arr->arg[arr->arg_count] = new;
	arr->arg_count++;
	return (0);
}

/*
	Checks wall texture's arguments for validity
	RETURN:
	if 0       - everything okay
	else if 1  - users' errors with arguments: look on custom message
	else if 2  - inside errors with program
*/
int	pars_valid_txtr(char *str, t_textures *arr)
{
	size_t		i;
	char		*path;

	i = 2;
	path = NULL;
	if (!str || !arr)
		return (2);
	if (ft_strncmp(str, "NO", 2) != 0 && ft_strncmp(str, "SO", 2) != 0
			&& ft_strncmp(str, "WE", 2) != 0 && ft_strncmp(str, "EA", 2) != 0)
		return (error_message());
	while (str[i])
	{
		if (str[i] == SKIP_SPACE)
			i++;
		else
		{
			if (path)
				return (error_message());
			path = take_path(str, &i);
			if (!path)
				return (2);
		}
	}
	add_new_side_elem(arr, path, str[0])
	return (0);
}
