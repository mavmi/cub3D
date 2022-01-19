/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:25:17 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/19 14:27:37 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_position	*pars_copy_position(t_position *pos)
{
	t_position	*cpy;

	if (!pos)
		return (NULL);
	cpy = (t_position *)malloc(sizeof(t_position));
	if (!cpy)
		return (NULL);
	cpy->x = pos->x;
	cpy->y = pos->y;
	return (cpy);
}
