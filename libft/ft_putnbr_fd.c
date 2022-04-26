/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 18:41:48 by pmaryjo           #+#    #+#             */
/*   Updated: 2021/09/05 18:41:49 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(char *digits, int size, int fd, int is_minus)
{
	if (is_minus)
	{
		ft_putchar_fd('-', fd);
	}
	while (size >= 0)
	{
		ft_putchar_fd(digits[size--], fd);
	}	
}

void	ft_putnbr_fd(int n, int fd)
{
	int			counter;
	char		digits[11];
	long int	num;
	int			is_minus;

	counter = 0;
	num = n;
	is_minus = 0;
	if (num == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (num < 0)
	{
		num *= -1;
		is_minus = 1;
	}
	while (num)
	{
		digits[counter++] = num % 10 + '0';
		num /= 10;
	}
	print(digits, counter - 1, fd, is_minus);
}
