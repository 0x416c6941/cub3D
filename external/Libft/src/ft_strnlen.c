/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:22:12 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:13:24 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (maxlen-- > 0 && s[i] != '\0')
		i++;
	return (i);
}
