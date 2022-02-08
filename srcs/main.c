/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:02:21 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/08 17:13:17 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/painting.h"

void	run(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		printf("Bad input\n");
		exit(1);
	}
	map = pars_get_map(argv[1]);
	if (!map)
	{
		printf("Parser error\n");
		exit(1);
	}
	paint(map);
}

int	main(int argc, char **argv)
{
	run(argc, argv);
	return (0);
}
