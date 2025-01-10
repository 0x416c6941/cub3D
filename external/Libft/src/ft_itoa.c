/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:30:27 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:07:44 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

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

/**
 * A helper for ft_itoa() (to bypass Norminette.)
 * @param	buf	A buffer where to save converted n.
 * @param	n	A number to convert to string.
 */
static void	ft_itoa_convert_n_to_str(char *str, int n)
{
	size_t	digits;
	size_t	i;
	int		buff;

	if (str == NULL)
		return ;
	else if (n < 0)
		*str++ = '-';
	digits = ft_count_digits(n);
	while (digits > 0)
	{
		buff = n;
		i = --digits;
		while (i-- > 0)
			buff /= 10;
		buff %= 10;
		if (buff < 0)
			buff = -buff;
		*str++ = '0' + buff;
	}
	*str = '\0';
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	res_size;

	res_size = ft_count_digits(n) + 1;
	if (n < 0)
		res_size++;
	res = (char *) malloc(res_size);
	if (res == NULL)
		return (NULL);
	ft_itoa_convert_n_to_str(res, n);
	return (res);
}
