/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:41:16 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:41:17 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*reserve_mem(int size, int is_minus)
{
	if (is_minus)
	{
		return ((char *)malloc(size + 2));
	}
	return ((char *)malloc(size + 1));
}

static char	*zero_str(void)
{
	char	*zero_str;

	zero_str = reserve_mem(1, 0);
	if (!zero_str)
		return (NULL);
	zero_str[0] = '0';
	zero_str[1] = '\0';
	return (zero_str);
}

static char	*array_to_str(char *digits, int size)
{
	int		i;
	int		j;
	char	*result_str;

	result_str = reserve_mem(size, digits[10] == '-');
	if (!result_str)
		return (NULL);
	j = size - 1;
	i = 0;
	if (digits[10] == '-')
		result_str[i++] = '-';
	while (j >= 0)
	{
		result_str[i++] = digits[j--];
	}
	result_str[i] = '\0';
	return (result_str);
}

char	*ft_itoa(int n)
{
	long int	num;
	int			counter;
	char		digits[11];

	num = n;
	counter = 0;
	digits[10] = '+';
	if (num == 0)
		return (zero_str());
	if (num < 0)
	{
		num *= -1;
		digits[10] = '-';
	}
	while (num != 0)
	{
		digits[counter++] = num % 10 + '0';
		num /= 10;
	}
	return (array_to_str(digits, counter));
}
