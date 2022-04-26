/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:42:00 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:42:01 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	counter;

	if (!dst || !src)
		return (0);
	if (!dstsize)
		return (ft_strlen(src));
	counter = 0;
	while (src[counter] && counter < dstsize - 1)
	{
		dst[counter] = src[counter];
		counter++;
	}
	if (counter < dstsize)
		dst[counter] = '\0';
	return (ft_strlen(src));
}
