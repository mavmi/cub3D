/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:42:06 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:42:07 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	substr_size;
	size_t	counter;
	char	*big;
	char	*smol;

	big = (char *)haystack;
	smol = (char *)needle;
	counter = 0;
	substr_size = ft_strlen(smol);
	if (substr_size == 0)
		return (big);
	if (big[0] == '\0')
		return (NULL);
	while (len >= substr_size && big[counter])
	{
		if (big[counter] == *smol
			&& ft_strncmp(smol, big + counter, substr_size) == 0)
		{
			return (big + counter);
		}
		counter++;
		len--;
	}
	return (NULL);
}
