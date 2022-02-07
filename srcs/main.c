/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:02:21 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/07 15:17:03 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../libft/libft.h"
#include "../include/geometry.h"
#include "../include/painting.h"
#include "../include/parser.h"
#include "../include/utils.h"

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
