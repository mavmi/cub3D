/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:41:58 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:41:59 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	c_dest;
	unsigned int	c_src;

	c_dest = 0;
	if (!dstsize)
		return (ft_strlen(src));
	c_dest = ft_strlen(dst);
	if (c_dest > dstsize)
		c_dest = dstsize;
	c_src = 0;
	while (src[c_src] != '\0' && c_dest < dstsize - c_src - 1)
	{
		dst[c_dest + c_src] = src[c_src];
		c_src++;
	}
	if (c_dest < dstsize)
		dst[c_dest + c_src] = '\0';
	return (c_dest + ft_strlen(src));
}
