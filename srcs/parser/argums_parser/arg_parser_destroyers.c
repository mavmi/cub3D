/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_destroyers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:17:52 by msalena           #+#    #+#             */
/*   Updated: 2022/02/13 17:39:46 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/arg_parser.h"

void	pars_destroy_txtr_arg(t_txtr_arg *destroyed)
{
	if (!destroyed)
		return ;
	free(destroyed->path);
	free(destroyed);
}

void	pars_destroy_textures(t_textures *destroyed)
{
	size_t	i;

	i = 0;
	if (!destroyed)
		return ;
	while (i < destroyed->arg_count)
	{
		pars_destroy_txtr_arg(destroyed->arg[i]);
		i++;
	}
	free(destroyed);
}

void	pars_destroy_ud_type(t_ud_type *destroyed)
{
	if (!destroyed)
		return ;
	free(destroyed);
}

void	pars_destroy_up_down(t_up_down *destroyed)
{
	size_t	i;

	i = 0;
	if (!destroyed)
		return ;
	while (i < destroyed->type_count)
	{
		pars_destroy_ud_type(destroyed->type[i]);
		i++;
	}
	free(destroyed);
}
