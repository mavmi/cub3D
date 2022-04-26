/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:42:08 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:42:09 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		counter;
	char	*ptr;

	counter = 0;
	ptr = (char *)s;
	while (*(ptr++))
	{
		counter++;
	}
	ptr = (char *)s;
	while (counter >= 0)
	{
		if (ptr[counter] == (char)c)
		{
			return (ptr + counter);
		}
		counter--;
	}
	return (NULL);
}
