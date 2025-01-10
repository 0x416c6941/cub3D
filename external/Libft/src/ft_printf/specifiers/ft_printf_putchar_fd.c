/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putchar_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:07:42 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:18:47 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_specifiers_common.h>
#include <unistd.h>

ssize_t	ft_printf_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
