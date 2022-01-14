/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:20:11 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/13 22:12:14 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

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

// Read file to map's struct.
// Return 0 if everything is ok,
// 1 otherwise
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
			return (NULL);
	}
	if (pars_read_file_handler(&arr, line))
		return (NULL);
	map = pars_str_arr_to_map(arr);
	utils_destroy_str_arr(arr);
	return (map);
}

// Read file and convert it's content
// to t_map struct.
// May return NULL
t_map	*pars_get_map(char *path)
{
	int		fd;
	t_map	*map;

	fd = pars_open_file(path);
	if (!path || fd < 0)
		return (NULL);
	map = pars_read_file(fd);
	close(fd);
	return (map);
}
