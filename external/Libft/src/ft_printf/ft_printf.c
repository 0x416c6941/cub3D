/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:39:43 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:17:41 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <ft_vfprintf_fd.h>

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	int				ret;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	ret = ft_vfprintf_fd(STDOUT_FILENO, format, ap);
	va_end(ap);
	return (ret);
}
