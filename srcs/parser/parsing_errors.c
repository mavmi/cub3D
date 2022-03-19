/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:26:52 by msalena           #+#    #+#             */
/*   Updated: 2022/03/19 16:08:53 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	errors(t_all code)
{
	if (code == ALL)
		printf("Error: invalid file's arguments\n");
	else if (code == TXTR)
		printf("Error: invalid texture arguments \n");
	else if (code == FC)
		printf("Error: invalid floor/ceiling arguments\n");
	else
	{
		printf("Error: invalid map \n");
		return (-1);
	}
	return (1);
}

int	error_destroy(t_argums *args, char error_message)
{
	pars_destroy_argums(args);
	if (error_message == 'y')
		return (errors(ALL));
	else
		return (1);
}
