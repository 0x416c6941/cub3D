/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:18:43 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:19:17 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_specifiers_common.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Returns an amount of digits in provided number
 * (basically a really stripped down version of log10()).
 * @param	num		Number to calculate digits in.
 * @return	Amount of digits in provided numbers.
 */
static size_t	ft_count_digits(int num)
{
	size_t	digits;

	digits = 0;
	while (42)
	{
		digits++;
		num /= 10;
		if (!num)
			break ;
	}
	return (digits);
}

/**
 * Bypass Norminette.
 * @param	nb		Digit of which number to write.
 * @param	digit	Digit (couting from 0 from right to left).
 * @param	fd		File descriptor where to write.
 * @return	(1), if successfully written it
 * 				(or some digit before it,
 * 				 if numbers is less that 'digit' digits);
 * 			(-1) otherwise.
 */
static ssize_t	ft_putdigit_fd(int nb, size_t digit, int fd)
{
	size_t	i;

	i = digit;
	while (i--)
		nb /= 10;
	nb %= 10;
	if (nb < 0)
		nb = -nb;
	return (ft_printf_putchar_fd('0' + nb, fd));
}

ssize_t	ft_printf_putnbr_fd(int nbr, int fd)
{
	ssize_t	ret;
	size_t	digits;

	ret = 0;
	if (nbr < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		ret++;
	}
	digits = ft_count_digits(nbr);
	while (digits)
	{
		if (ft_putdigit_fd(nbr, --digits, fd) == -1)
			return (-1);
		ret++;
	}
	return (ret);
}
