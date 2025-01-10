/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specifiers_common.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:59:38 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:17:06 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_SPECIFIERS_COMMON_H
# define FT_PRINTF_SPECIFIERS_COMMON_H

/**
 * Some of the functions here are modified version of those from Libft,
 * which will return the return value depending on the result
 * of their write() function call.
 */

# include <sys/types.h>
# include <stdarg.h>
# include <stdint.h>

ssize_t	ft_printf_putchar_fd(char c, int fd);
ssize_t	ft_printf_putstr_fd(const char *s, int fd);
ssize_t	ft_printf_putnbr_base_fd(unsigned int nbr, const char *base, int fd);
ssize_t	ft_printf_putptr_fd(uintptr_t ptr, int fd);
ssize_t	ft_printf_putnbr_fd(int nbr, int fd);

#endif	/* FT_PRINTF_SPECIFIERS_COMMON_H */
