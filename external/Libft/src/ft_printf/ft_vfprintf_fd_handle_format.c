/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf_fd_handle_format.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:22:47 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:18:07 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_vfprintf_fd_handle_format.h>
#include <sys/types.h>
#include <ft_printf_specifiers_common.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

/**
 * Checks, if the provided character is a specifier or not.
 * If yes, then '*out' will also contain the respective value.
 * @warning	out can't be NULL.
 * @param	c	Character to check.
 * @param	out	Where to save that mentioned respective value.
 * @return	Some non-negative value, if yes;
 * 			(-1) otherwise.
 */
static int	ft_check_specifier(char c, enum e_specifier *out)
{
	if (c == 'c')
		*out = c_spec;
	else if (c == 's')
		*out = s_spec;
	else if (c == 'p')
		*out = ptr_spec;
	else if (c == 'd')
		*out = d_spec;
	else if (c == 'i')
		*out = i_spec;
	else if (c == 'u')
		*out = u_spec;
	else if (c == 'x')
		*out = lx_spec;
	else if (c == 'X')
		*out = ux_spec;
	else if (c == '%')
		*out = pc_spec;
	else
		return (-1);
	return (0);
}

/**
 * Calls the output function respective to value stored in 'spec'.
 * @param	fd		File descriptor, to which output function
 * 					should produce it's output.
 * @param	spec	Specifier.
 * @param	ap		Argument pointer.
 * @return	return value of a respective function;
 * 			If value in 'spec' is somehow corrupted, (-1).
 */
static ssize_t	ft_process_specifier(int fd, enum e_specifier spec, va_list ap)
{
	if (spec == c_spec)
		return (ft_printf_putchar_fd((char)va_arg(ap, int), fd));
	else if (spec == s_spec)
		return (ft_printf_putstr_fd(va_arg(ap, const char *), fd));
	else if (spec == ptr_spec)
		return (ft_printf_putptr_fd(va_arg(ap, uintptr_t), fd));
	else if (spec == d_spec)
		return (ft_printf_putnbr_fd(va_arg(ap, int), fd));
	else if (spec == i_spec)
		return (ft_printf_putnbr_fd(va_arg(ap, int), fd));
	else if (spec == u_spec)
		return (ft_printf_putnbr_base_fd(va_arg(ap, unsigned int),
				"0123456789", fd));
	else if (spec == lx_spec)
		return (ft_printf_putnbr_base_fd(va_arg(ap, unsigned int),
				"0123456789abcdef", fd));
	else if (spec == ux_spec)
		return (ft_printf_putnbr_base_fd(va_arg(ap, unsigned int),
				"0123456789ABCDEF", fd));
	else if (spec == pc_spec)
		return (ft_printf_putchar_fd('%', fd));
	return (-1);
}

/**
 * About flags:
 *
 * ' ' is ignored when '+' is used;
 * '0' is ignored when '-' is used;
 * '0' is ignored when precision is set.
 * For 'o', 'x' and 'X' specifiers, '#' is ignored, if provided precision
 * 	is 0, and the value of the number to print is 0 as well.
 * If there's no value after the precision's '.' sign, behavior is undefined.
 * '.' can only be used once. If it's met more than once,
 * 	then the behavior is undefined.
 * If no flag, precision specifier, etc. is specified after the '%' sign,
 * 	the behavior is undefined.
 */
ssize_t	ft_vfprintf_fd_handle_format(int fd, const char **format, va_list ap)
{
	enum e_specifier	specifier;

	if (format == NULL || *format == NULL || **format != '%')
		return (0);
	(*format)++;
	if (ft_check_specifier(**format, &specifier) == -1)
		return (ft_printf_putchar_fd('%', fd));
	(*format)++;
	return (ft_process_specifier(fd, specifier, ap));
}
