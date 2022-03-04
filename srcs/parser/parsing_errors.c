/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:26:52 by msalena           #+#    #+#             */
/*   Updated: 2022/03/04 19:26:53 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_parser.h"

int errors(void)
{
	printf("Error: invalid file's arguments\n");
	return (1);
}

int	error_texture_message(void)
{
	printf("Error: invalid texture arguments \n");
	return (1);
}

int	error_ud_message(void)
{
	printf("Error: invalid floor/ceiling arguments\n");
	return (1);
}

/*
	Free freed and input sms about
	invalide argums if sms_fl == 'y'
*/
void	*free_return(size_t *freed, char sms_fl)
{
	if (sms_fl && sms_fl == 'y')
		error_ud_message();
	free(freed);
	return (NULL);
}


int	error_destroy(t_argums *args, char error_message)
{
	pars_destroy_up_down(args->ud_arr);
	pars_destroy_textures(args->txtr_arr);
	if (error_message == 'y')
		return (errors());
	else
		return (1);
}
