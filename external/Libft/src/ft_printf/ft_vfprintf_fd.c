/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:04:57 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:17:51 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_vfprintf_fd.h>
#include <sys/types.h>
#include <stddef.h>
#include <unistd.h>
#include <ft_vfprintf_fd_handle_format.h>

int	ft_vfprintf_fd(int fd, const char *format, va_list ap)
{
	int		ret;
	ssize_t	bytes_written;

	if (format == NULL)
		return (-1);
	ret = 0;
	while (*format != '\0')
	{
		if (*format != '%')
		{
			if (write(fd, format++, 1) == -1)
				return (-1);
			ret++;
			continue ;
		}
		bytes_written = ft_vfprintf_fd_handle_format(fd, &format, ap);
		if (bytes_written == -1)
			return (-1);
		ret += bytes_written;
	}
	return (ret);
}
