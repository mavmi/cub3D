/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:18:59 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 16:37:57 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

static int	exit_with_error(char **line, char **result)
{
	free(*result);
	*result = NULL;
	*line = NULL;
	return (-1);
}

static int	get_line(char **line, char **result, char *n_ptr)
{
	char	*tmp_str;

	if (n_ptr)
	{
		*line = ft_substr(*result, 0, n_ptr - *result);
		tmp_str = ft_substr(*result, n_ptr - *result + 1,
				ft_strlen(*result) - (n_ptr - *result));
		free(*result);
		*result = tmp_str;
		return (1);
	}
	else if (!ft_strlen(*result))
		*line = ft_strdup(NULL);
	else
		*line = ft_strdup(*result);
	free(*result);
	*result = NULL;
	return (0);
}

static int	gnl_handler(int fd, char **line, char *buffer)
{
	int			read_bytes;
	char		*n_ptr;
	static char	*result = NULL;

	if (!result)
		result = ft_strdup(NULL);
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (exit_with_error(line, &result));
		buffer[read_bytes] = '\0';
		if (append_str(&result, buffer))
			return (exit_with_error(line, &result));
		n_ptr = ft_strchr(result, '\n');
		if (n_ptr || !read_bytes)
			return (get_line(line, &result, n_ptr));
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int		val;
	char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	val = gnl_handler(fd, line, buffer);
	free(buffer);
	return (val);
}
