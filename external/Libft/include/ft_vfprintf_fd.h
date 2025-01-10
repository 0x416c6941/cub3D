/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf_fd.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:02:02 by asagymba          #+#    #+#             */
/*   Updated: 2024/09/21 23:04:47 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VFPRINTF_FD_H
# define FT_VFPRINTF_FD_H

# include <stdarg.h>

/**
 * The same thing as vfprintf(), but uses
 * POSIX's file descriptors as an argument.
 * @param	fd		A file descriptor for the output.
 * @param	format	A format specifier.
 * @param	ap		Argument pointer.
 * @return	Amount of characters written to fd;
 * 			some negative value in case of error.
 */
int	ft_vfprintf_fd(int fd, const char *format, va_list ap);

#endif	/* FT_VFPRINTF_FD_H */
