/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:09:21 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:19:45 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_specifiers_common.h>
#include <stddef.h>
#include <unistd.h>

ssize_t	ft_printf_putstr_fd(const char *s, int fd)
{
	ssize_t	ret;

	if (s == NULL)
		return (ft_printf_putstr_fd("(null)", fd));
	ret = 0;
	while (*s != '\0')
	{
		if (write(fd, s++, 1) == -1)
			return (-1);
		ret++;
	}
	return (ret);
}
