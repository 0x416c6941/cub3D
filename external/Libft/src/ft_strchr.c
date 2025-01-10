/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:45:54 by asagymba          #+#    #+#             */
/*   Updated: 2024/11/23 20:11:19 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	while (42)
	{
		if (*s == (char)c)
			return ((char *)s);
		else if (*s++ == '\0')
			break ;
	}
	return (NULL);
}
