/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:49:26 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:13:39 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*os;

	os = s;
	s += ft_strlen(s);
	while (42)
	{
		if (*s == (char)c)
			return ((char *)s);
		else if (s-- == os)
			break ;
	}
	return (NULL);
}
