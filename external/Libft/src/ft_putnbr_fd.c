/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:12:58 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:10:41 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <unistd.h>

/**
 * Returns an amount of digits in provided number
 * (basically a really stripped down version of log10()).
 * @param	n	Number to calculate amount of digits in.
 * @return	Amount of digits in provided numbers.
 */
static size_t	ft_count_digits(int n)
{
	size_t	digits;

	digits = 0;
	while (42)
	{
		digits++;
		n /= 10;
		if (!n)
			break ;
	}
	return (digits);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	digits;
	size_t	i;
	int		buff;

	if (n < 0)
		if (write(fd, "-", 1) == -1)
			return ;
	digits = ft_count_digits(n);
	while (digits)
	{
		buff = n;
		i = --digits;
		while (i--)
			buff /= 10;
		buff %= 10;
		if (buff < 0)
			buff = -buff;
		buff += '0';
		if (write(fd, &buff, 1) == -1)
			return ;
	}
}
