/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:42:09 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:42:10 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_empty_str(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

static int	is_in_set(char const *set, char c)
{
	if (!set)
		return (1);
	while (*set)
	{
		if (*set == c)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

static int	is_set_only(char const *s1, char const *set)
{
	while (*s1)
	{
		if (!is_in_set(set, *s1))
			return (0);
		s1++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	if (!s1[0] || is_set_only(s1, set))
		return (get_empty_str());
	begin = 0;
	while (s1[begin] && is_in_set(set, s1[begin]))
		begin++;
	end = ft_strlen(s1) - 1;
	while (end >= 0 && is_in_set(set, s1[end]))
		end--;
	result = ft_substr(s1, begin, end - begin + 1);
	return (result);
}
