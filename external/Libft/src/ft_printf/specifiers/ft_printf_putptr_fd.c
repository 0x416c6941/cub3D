/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putptr_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:02:32 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:19:33 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_specifiers_common.h>
#include <libft.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Converts nbr to base numerical system and saves the result to out.
 * @warning	Result is reversed.
 * @warning	'base' needs to be a valid base.
 * @param	nbr		Pointer to convert.
 * @param	base	Numerical system's characters.
 * @param	out		Buffer to save the result to.
 * @return	strlen(out), basically a length of resulting string.
 **/
static size_t	ft_convert_to_base_ptrhack(uintptr_t nbr,
		const char *base, char *out)
{
	size_t		base_size;
	size_t		i;
	uintptr_t	mod;

	base_size = ft_strlen(base);
	i = 0;
	while (nbr)
	{
		mod = nbr % base_size;
		out[i++] = base[mod];
		nbr /= base_size;
	}
	if (!i)
		out[i++] = *base;
	out[i] = '\0';
	return (i);
}

#undef CONVERTED_SIZE
/**
 * 999 bytes and '\0'.
 */
#define CONVERTED_SIZE	1000

/**
 * Prints the nbr in a numerical system, provided in 'base', to 'fd.'.
 * The dirtiest hack ever possible.
 * @warning	'base' needs to be a valid base.
 * @param	nbr		Pointer to print (without "0x" header).
 * @param	base	Numerical system.
 * @param	fd		A file descriptor where to store the output.
 * @return	Amount of written bytes to fd.
 */
ssize_t	ft_putnbr_base_fd_ptrhack(uintptr_t nbr, const char *base, int fd)
{
	ssize_t	ret;
	char	converted[CONVERTED_SIZE];
	size_t	i;

	ret = 0;
	i = ft_convert_to_base_ptrhack(nbr, base, converted) - 1;
	while (42)
	{
		if (write(fd, converted + i, 1) == -1)
			return (-1);
		ret++;
		if (!i--)
			break ;
	}
	return (ret);
}

#undef CONVERTED_SIZE

/**
 * Actually, if ptr == 0, then behavior is undefined, but
 * let's still handle this behavior :p
 */
ssize_t	ft_printf_putptr_fd(uintptr_t ptr, int fd)
{
	ssize_t	ret;
	ssize_t	putnbr_base_fd_status;

	if (ptr == 0)
		return (ft_printf_putstr_fd("(nil)", fd));
	ret = ft_printf_putstr_fd("0x", fd);
	if (ret == -1)
		return (-1);
	putnbr_base_fd_status = ft_putnbr_base_fd_ptrhack(ptr, "0123456789abcdef",
			fd);
	if (putnbr_base_fd_status == -1)
		return (-1);
	return (ret + putnbr_base_fd_status);
}
