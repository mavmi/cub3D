/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:20:11 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/03/04 19:26:47 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_parser.h"

/*
	Pushback [line] to [arr].
	Return 0 if everything is ok, 1 otherwise
*/
static int	pars_read_file_handler(char ***arr, char *line)
{
	int	return_status;

	return_status = utils_str_arr_push_bach(arr, line);
	if (return_status)
	{
		free(line);
		utils_destroy_str_arr(*arr);
		return (1);
	}
	return (0);
}

/*
	Read input file line by line,
	save it to an array of strings and
	call pars_str_arr_to_map(..)
	to convert it to t_map struct.
	May return NULL
*/
static t_map	*pars_read_file(int fd)
{
	t_map	*map;
	char	**arr;
	char	*line;

	if (fd < 0)
		return (NULL);
	arr = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (pars_read_file_handler(&arr, line))
			return (NULL); // castomer sms about not reading
	}
	if (pars_read_file_handler(&arr, line))
		return (NULL); // castomer sms about not reading
		for (int i = 0; arr[i]; i++)
			printf ("%s\n", arr[i]);
	////////////function which parsing arguments before map////////////
	printf ("\n~~~~~~~ %d\n", pars_arg_definition(arr));
	sleep(10);
	exit (1);
	map = pars_str_arr_to_map(arr);
	utils_destroy_str_arr(arr);
	return (map);
}

/*
	Read file and convert it's content
	to t_map struct.
	May return NULL
*/
t_map	*pars_start(char *path)
{
	int		fd;
	t_map	*map;

	fd = pars_open_file(path);
	if (!path || fd < 0)
		return (NULL); // should be needing printing error from open function
	map = pars_read_file(fd);
	close(fd);
	return (map);
}
