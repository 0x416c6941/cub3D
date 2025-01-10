/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:56:07 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:12:57 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = 0;
	while (*src != '\0')
	{
		if (size > 1 && dst != NULL)
		{
			*dst++ = *src;
			size--;
		}
		src_len++;
		src++;
	}
	if (size > 0 && dst != NULL)
		*dst = '\0';
	return (src_len);
}
