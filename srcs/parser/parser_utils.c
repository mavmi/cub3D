/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:12:44 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/13 14:50:36 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// Open file with read only mode and
// and return it's fd
int	pars_open_file(char *path)
{
	return (open(path, O_RDONLY));
}

int	pars_is_char_valid_square(char c)
{
	if (c != VOID && c != EMPTY && c != WALL)
		return (0);
	return (1);
}

int	pars_is_char_valid_player(char c)
{
	if (c != NORTH_OR && c != SOUTH_OR
		&& c != EAST_OR && c != WEST_OR)
		return (0);
	return (1);
}

int	pars_is_char_valid(char c)
{
	if (!pars_is_char_valid_square(c) && !pars_is_char_valid_player(c))
		return (0);
	return (1);
}

// Check if string containg allowed chars only
int	pars_is_str_valid(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!pars_is_char_valid(*str))
			return (0);
		str++;
	}
	return (1);
}
