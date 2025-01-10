/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf_fd_handle_format.h                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:16:39 by asagymba          #+#    #+#             */
/*   Updated: 2024/09/24 21:15:20 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VFPRINTF_FD_HANDLE_FORMAT_H
# define FT_VFPRINTF_FD_HANDLE_FORMAT_H

# include <sys/types.h>
# include <stdarg.h>

enum	e_specifier
{
	c_spec,
	s_spec,
	ptr_spec,
	d_spec,
	i_spec,
	u_spec,
	lx_spec,
	ux_spec,
	pc_spec,
};

/**
 * Handle some formatted data, format of which
 * is specified in 'format', which starts by '%'.
 * Format also will be shifted to point outside of the current specifier.
 * @warning	If format specifier is invalid, behavior is undefined.
 * @param	fd		A file descriptor for the output.
 * @param	format	A pointer to a format of the data.
 * @param	ap		Argument pointer.
 * @return	Amount of characters written to fd;
 * 			(-1), if got some error.
 */
ssize_t	ft_vfprintf_fd_handle_format(int fd, const char **format, va_list ap);

#endif	/* FT_PRINTF_HANDLE_FORMAT_H */
