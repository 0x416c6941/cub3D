/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:26:11 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:10:13 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/**
 * Overlapping becomes a problem, only if (src < dest).
 * If that's the case, then we need to copy from the end to beginning,
 * otherwise we can proceed as usually (from beginning to end).
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;

	if (dest == NULL)
		return (NULL);
	pdest = dest;
	psrc = src;
	if (!(src < dest))
	{
		while (n-- > 0)
			*pdest++ = *psrc++;
	}
	else
	{
		pdest += n;
		psrc += n;
		while (n-- > 0)
			*--pdest = *--psrc;
	}
	return (dest);
}
