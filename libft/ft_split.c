/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:41:51 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:41:51 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_arr(char ***array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free((*array)[i++]);
	}
	free(*array);
}

static int	get_str_cnt(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
	}
	return (count);
}

static char	*get_string(char const *s, char c, int begin)
{
	int		i;
	int		end;
	char	*str;

	i = 0;
	end = begin;
	while (s[end] != c && s[end] != '\0')
		end++;
	str = (char *)malloc(end - begin + 1);
	if (!str)
		return (NULL);
	while (begin + i != end)
	{
		str[i] = s[i + begin];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**get_arr(const char *s, char c)
{
	if (!s)
		return (NULL);
	return ((char **)malloc((get_str_cnt(s, c) + 1) * sizeof(char **)));
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**array;

	array = get_arr(s, c);
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		array[j++] = get_string(s, c, i);
		if (array[j - 1] == NULL)
		{
			free_arr(&array, j - 1);
			return (NULL);
		}
		i += ft_strlen(array[j - 1]);
	}
	array[j] = NULL;
	return (array);
}
