/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:02:21 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/08 14:44:39 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/painting.h"

int	check_filename(char *argum_file)
{
	size_t	i;

	i = 0;
	while (argum_file[i])
	{
		if (argum_file[i] == '.')
			break ;
		i++;
	}
	if (argum_file[i++] != '.')
		return (1);
	if ((ft_strncmp((argum_file + i), "cub", 3)) != 0)
		return (1);
	return (0);
}

void	run(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2 || check_filename(argv[1]))
	{
		printf("Bad input: agrument should be: <file.cub>\n");
		exit(1);
	}
	map = pars_start(argv[1]);
	if (!map)
	{
		exit(1);
	}
	if (!map->player)
	{
		pars_destroy_map(map);
		errors(MAP);
		exit (1);
	}
	paint(map);
}

int	main(int argc, char **argv)
{
	run(argc, argv);
	return (0);
}
