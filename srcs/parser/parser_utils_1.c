/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:12:44 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/27 19:16:53 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// Open file with read only mode and
// and return it's fd
int	pars_open_file(char *path)
{
	return (open(path, O_RDONLY));
}

// Check if input char is valid square char.
// Return 1 if it is, 0 otherwise
int	pars_is_char_valid_square(char c)
{
	if (c != MAP_SQ_VOID && c != MAP_SQ_EMPTY && c != MAP_SQ_WALL)
		return (0);
	return (1);
}

// Check if input char is valid player char.
// Return 1 if it is, 0 otherwise
int	pars_is_char_valid_player(char c)
{
	if (c != MAP_OR_NORTH && c != MAP_OR_SOUTH
		&& c != MAP_OR_EAST && c != MAP_OR_WEST)
		return (0);
	return (1);
}

// Check if input char is valid square or player char.
// Return 1 if it is, 0 otherwise
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
