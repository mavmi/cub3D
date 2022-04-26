/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:18:54 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/02/02 16:38:06 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*ptr;

	if (!s1)
	{
		ptr = malloc(1);
		if (ptr)
			ptr[0] = '\0';
		return (ptr);
	}
	len = ft_strlen(s1);
	ptr = (char *)malloc(len + 1);
	if (ptr == NULL)
		return (ptr);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	if (!s)
		return (0);
	counter = 0;
	while (*(s++))
	{
		counter++;
	}
	return (counter);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	if (c == '\0')
		return (ptr);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		counter;
	size_t		sub_str_size;
	char		*result;

	if (!s || start >= ft_strlen(s))
		return (ft_strdup(NULL));
	counter = 0;
	sub_str_size = ft_strlen(s) - start;
	if (sub_str_size >= len)
		sub_str_size = len;
	sub_str_size++;
	result = (char *)malloc(sub_str_size);
	if (!result)
		return (NULL);
	s += start;
	while (*s && len--)
		result[counter++] = *s++;
	result[counter] = '\0';
	return (result);
}

int	append_str(char **str_to_app, char *buffer)
{
	int		counter;
	char	*str;
	char	*result;

	str = *str_to_app;
	if (!buffer)
		return (1);
	if (!str)
		return (2);
	result = (char *)malloc(ft_strlen(str) + ft_strlen(buffer) + 1);
	if (!result)
		return (3);
	counter = 0;
	while (*str)
		result[counter++] = *str++;
	while (*buffer)
		result[counter++] = *buffer++;
	result[counter] = '\0';
	free(*str_to_app);
	*str_to_app = result;
	return (0);
}
