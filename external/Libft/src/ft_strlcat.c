/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:50:29 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:12:51 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ret;

	ret = 0;
	while (size > 0 && dst != NULL && *dst != '\0')
	{
		dst++;
		size--;
		ret++;
	}
	while (*src != '\0')
	{
		if (size > 1 && dst != NULL)
		{
			*dst++ = *src;
			size--;
		}
		ret++;
		src++;
	}
	if (size > 0 && dst != NULL)
		*dst = '\0';
	return (ret);
}
