/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_getters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:50:46 by msalena           #+#    #+#             */
/*   Updated: 2022/03/13 18:38:34 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

t_txtr_arg	*pars_get_new_txtr_arg(char side, char *path)
{
	t_txtr_arg	*new;

	if (!side || !path)
		return (NULL);
	new = (t_txtr_arg *)malloc(sizeof(t_txtr_arg));
	if (!new)
		return (NULL);
	new->side = side;
	new->path = path;
	return (new);
}

t_textures	*pars_get_empty_textures(void)
{
	t_textures	*new;

	new = (t_textures *)malloc(sizeof(t_textures));
	if (!new)
		return (NULL);
	new->arg = (t_txtr_arg **)malloc(sizeof(t_txtr_arg *) * 15);
	if (!new->arg)
	{
		free(new);
		return (NULL);
	}
	new->arg_count = 0;
	return (new);
}

t_ud_type	*pars_get_new_ud_type(char type, size_t red,
										size_t green, size_t blue)
{
	t_ud_type	*new;

	if (!type)
		return (NULL);
	new = (t_ud_type *)malloc(sizeof(t_ud_type));
	if (!new)
		return (NULL);
	new->type = type;
	new->red = red;
	new->green = green;
	new->blue = blue;
	return (new);
}

t_up_down	*pars_get_empty_up_down(void)
{
	t_up_down	*new;

	new = (t_up_down *)malloc(sizeof(t_up_down));
	if (!new)
		return (NULL);
	new->type = (t_ud_type **)malloc(sizeof(t_ud_type *) * 2);
	if (!new->type)
	{
		free(new);
		return (NULL);
	}
	new->type_count = 0;
	return (new);
}
