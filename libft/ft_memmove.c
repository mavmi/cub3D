/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:41:40 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:41:41 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			c;
	unsigned char	*d;
	unsigned char	*s;

	c = 0;
	if (dst == (void *)src)
		return (dst);
	d = (unsigned char *)(dst + len - 1);
	s = (unsigned char *)(src + len - 1);
	if (src - dst < 0)
	{
		while (len-- > 0)
		{
			*(d--) = *(s--);
		}
	}
	else
	{
		while (c < len)
		{
			*(unsigned char *)(dst + c) = *(const unsigned char *)(src + c);
			c++;
		}
	}
	return (dst);
}
